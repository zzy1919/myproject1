#include "process_comm.h"

// Data
string Data::getData(){
    return data_;
};

// ProcessIdData
ProcessIdData& ProcessIdData::getInstance(){
    static ProcessIdData instance;
    return instance;
};

string ProcessIdData::makeData(){
    cout << "进程id获取：" << getpid() <<endl;
    return "进程id获取" + to_string(getpid());
};


// DiskUsageData
DiskUsageData& DiskUsageData::getInstance(){
    static DiskUsageData instance;
    return instance;
};

string DiskUsageData::makeData(){
    std::ifstream stat("/proc/self/stat");
    if (!stat) {
        std::cerr << "Failed to open /proc/self/stat" << std::endl;
        return "false";
    }

    // 获取第24个字段（存储在stat文件中），该字段表示当前进程的已分配块数（以512字节为单位）
    std::string dummy;
    for (int i = 0; i < 23; ++i){
        stat >> dummy;
    }

    unsigned long long diskUsage;
    stat >> diskUsage;

    // 将已分配块数转换为字节
    diskUsage *= 512;
    
    cout << "磁盘占用获取：" << diskUsage << "B" << endl;
    return "磁盘占用获取：" + to_string(diskUsage) + " B";
};

// Transfer
Data* Transfer::createData(GetDataMethod method){
    if (method == ProcessIdMethod){
        Data* ptr = &ProcessIdData::getInstance();
        return ptr;
    }
    else if (method == DiskUsageMethod){
        Data* ptr = &DiskUsageData::getInstance();
        return ptr;
    }
    else{
        cout << "log  error method" << endl;
        
    }
    return nullptr;
}

string Transfer::getSendData(){
    return senddata_;
};

string Transfer::getAcceptData(){
    return acceptdata_;
};

// pipe
int PipeTransfer::pipefd_[2] = {0,0};

void PipeTransfer::send(){
    Data* ptr = createData(gdm_);
    string transfer_str = "pipe send " + ptr->makeData() + "当前时间" + getNowTime();
    cout <<  transfer_str << endl;
    if (fork() == 0){

        close(pipefd_[0]);
        write(pipefd_[1], transfer_str.c_str(), strlen(transfer_str.c_str()));
        
        this_thread::sleep_for(chrono::seconds(1));
        string transfer_str_son ="pipe send sonpid" +  ptr->makeData();
        cout <<  transfer_str_son << endl;
        write(pipefd_[1], transfer_str_son.c_str(), strlen(transfer_str_son.c_str()));
        close(pipefd_[1]);
        exit(0);
    }
};

void PipeTransfer::accept(){
    char buffer[100];
    read(pipefd_[0], buffer, sizeof(buffer));
    std::cout << "pipe accept : " << buffer << std::endl;

    this_thread::sleep_for(chrono::seconds(3));
    memset(buffer, 0, sizeof(buffer));
    read(pipefd_[0], buffer, sizeof(buffer));
    std::cout << "pipe accept : " << buffer << std::endl;

    close(pipefd_[0]);
};

// memory
void MemoryTransfer::send(){
    Data* ptr = createData(gdm_);

    string transfer_str = ptr->makeData() + "当前时间" + getNowTime();
    
    // 将共享内存段连接到当前进程的地址空间
    void* shmem = shmat(shm_id_, NULL, 0);
    if (shmem == (void*)-1) {
        perror("shmat");
        return ;
    }   

    // "/shmem_mutex" 文件系统唯一， O_CREAT不存在则创建， 权限0666，初始值 1
    sem_t* mutex = sem_open("/shmem_mutex", O_CREAT, 0666, 1);
    sem_t* cond_var = sem_open("/shmem_cond_var", O_CREAT, 0666, 0);
    // 共享内存写入 

    sem_wait(mutex);
    strncpy((char *)shmem, transfer_str.c_str(), SHARE_MEMORY_SIZE);
    cout << "memory send " << transfer_str << endl;
    sem_post(mutex);
    sem_post(cond_var);
    
    // 关闭信号量
    sem_close(mutex);
    sem_close(cond_var);
    // 使用完共享内存后，与进程分离
    if (shmdt(shmem) == -1){
        perror("shdmt");
        return;
    }

};

void MemoryTransfer::accept(){


    void* shmem = shmat(shm_id_, NULL, 0);
    if (shmem == (void*)-1) {
        perror("shmat");
        return;
    }   

    sem_t* mutex = sem_open("/shmem_mutex", O_CREAT, 0666, 1);
    sem_t* cond_var = sem_open("/shmem_cond_var", O_CREAT, 0666, 0); 

    char buffer[SHARE_MEMORY_SIZE];
    sem_wait(cond_var);
    sem_wait(mutex);

    strncpy(buffer, (char*)shmem, SHARE_MEMORY_SIZE);
    string message = "share memory accept" + string(buffer);
    cout << message << endl;
    sem_post(mutex);

    // 关闭并删除 锁和信号量
    sem_close(mutex);
    sem_close(cond_var);
    sem_unlink("/shmem_mutex");
    sem_unlink("/shmem_cond_var");
    // 删除共享内存段
    if (shmctl(shm_id_, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        return ;
    }
};

void MemoryTransfer::ClearSemAndMemory(){
    
    sem_unlink("/shmem_mutex");
    sem_unlink("/shmem_cond_var");
    // 删除共享内存段
    if (shmctl(shm_id_, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        return ;
    }
}

Transfer* DataTransferFactory::getTransfer(GetDataMethod gdm, CommMode cm){
    if (cm == PipeMode){
        Transfer* ptr =  new PipeTransfer(gdm);
        return ptr;
    }
    else if (cm == MemoryMode){
        Transfer*ptr = new MemoryTransfer(gdm);
        return ptr;
    }
}
