#include <iostream>
#include <string>
#include <string.h>

//子进程、管道相关
#include "unistd.h"
#include <thread>

// 时间
#include <chrono>
#include <time.h>

// 文件操作库
#include <fstream>

//获取资源使用情况
#include <sys/resource.h>
#include <sys/statvfs.h>
#include <sys/vfs.h>

// 共享内存操作
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

// 添加信号量头文件
#include <semaphore.h>  
#include <fcntl.h>


#define SHARE_MEMORY_SIZE 1024



using namespace std;

enum GetDataMethod{ 
    ProcessIdMethod = 1,
    DiskUsageMethod = 2
};

enum CommMode{
    PipeMode = 1,
    MemoryMode = 2
};


class Data{
private:
    string data_ = "";
public:
    virtual string makeData()=0;
    string getData();
};

class ProcessIdData : public Data{
private:
    ProcessIdData(){};
public:
    string makeData();    
    static ProcessIdData& getInstance(); 
};

class DiskUsageData : public Data{
private:
    DiskUsageData(){};
public:
    static DiskUsageData& getInstance();
    string makeData();
};

class Transfer{
private:
    string senddata_ = "";
    string acceptdata_ = "";

public:
    virtual void send() = 0;
    virtual void accept() = 0;
    string getSendData();
    string getAcceptData();
    Data* createData(GetDataMethod method);
    string getNowTime(){
        time_t timep;
        time(&timep);
        return ctime(&timep);
    }
};

class PipeTransfer: public Transfer{
private:
    static int pipefd_[2];
    GetDataMethod gdm_;
public:
    PipeTransfer(GetDataMethod gdm):gdm_(gdm){
        if (pipe(pipefd_) == -1)
        std::cout << "Failed to create pipe." << std::endl;
    };
    void send() override;
    void accept() override;
};

class MemoryTransfer: public Transfer{
private:
    GetDataMethod gdm_;
public:
    MemoryTransfer(GetDataMethod gdm):gdm_(gdm){
        key_t key = ftok(".", 'M');
        shm_id_ = shmget(key, SHARE_MEMORY_SIZE, IPC_CREAT|0666);
        if (shm_id_ == -1){
            perror("shmget");
            return;
        }
    };
    int shm_id_; //共享内存key
    void send() override;
    void accept() override;
    void ClearSemAndMemory();
};

class DataTransferFactory{
public:
    Transfer* getTransfer(GetDataMethod gdm, CommMode cm); 
};





