// #include<iostream>
// #include"hello.h"
// #include"gtest/gtest.h"
// #include "leetc_ques.h"
// #include <map>
// #include <chrono>
// #include <thread>
// #include "opencv2/opencv.hpp"

// using namespace std;
// using namespace cv;


// void func(int questionNum);
// void func72();
// void func2697();
// void func2008();
// void func2415();

// int main(int argc, char** argv)
// {
//     // ::testing::InitGoogleTest();
//     // // 创建并添加自定义监听器
//     // ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
//     // CustomTestListener* listern_ptr = new CustomTestListener();
//     // listeners.Append(listern_ptr);

//     // // ::testing::GTEST_FLAG(filter) = "q72.q";
//     // ::testing::GTEST_FLAG(filter) = "q2697.q";
//     // RUN_ALL_TESTS();
//     // cout << listern_ptr->failtests << endl;
//     cout << funcPrintf() << endl;
//     cout << "main hello" << endl;
//     // func2415();

//     std::map<int, std::string> userMap = {{1, "Alice"}, {2, "Bob"}, {3, "Charlie"}};

//     for (const auto& [key, value] : userMap) {
//         std::cout << "Key: " << key << ", Value: " << value << std::endl;
//     }

//     Mat image;
//     image = imread("/home/zzy/Desktop/zzy_stduy/my_project_test1/source/1.png");
//     if (image.empty())
// 		std::cout << "image is empty or the path is invalid!" << std::endl;
//     namedWindow("Display Image", WINDOW_AUTOSIZE );
//     imshow("Display Image", image);
//     waitKey(0);

//     return 0;
// }

// // TEST(q72, q){
// //     Solution72 s72;
// //     EXPECT_EQ(s72.minDistance(word1, word2), 2);
// //     EXPECT_EQ(s72.minDistance(word1, word2), s72.minDistance(word1, word2) + 1);
// //     EXPECT_EQ(s72.minDistance(word1, word2), 1);
// // }

// // TEST(q2697, q){
// //     Solution2697 s2697;
// //     EXPECT_EQ(s2697.makeSmallestPalindrome("egcfe"), "efcfe");
// //     EXPECT_EQ(s2697.makeSmallestPalindrome("abcd"), "abba");
// //     EXPECT_EQ(s2697.makeSmallestPalindrome("seven"), "neven");
// //     EXPECT_EQ(s2697.makeSmallestPalindrome("c"), "c");
// // }

// void func(int questionNum){
//     if (questionNum == 72){
//         func72();
//     }
//     if (questionNum == 2697){
//         func2697();
//     }
// }

// void func72(){
//     int a=0;
// }

// void func2697(){
//     Solution2697 s2697;
//     string s = "egcfe";
//     string res = s2697.makeSmallestPalindrome(s);

//     EXPECT_EQ(s2697.makeSmallestPalindrome("egcfe"), "efcfe");
//     EXPECT_EQ(s2697.makeSmallestPalindrome("abcd"), "abba");
//     EXPECT_EQ(s2697.makeSmallestPalindrome("seven"), "neven");
//     EXPECT_EQ(s2697.makeSmallestPalindrome("c"), "c");

//     cout << res << endl;
// }

// void func2008(){
//     Solution2008 s2008;
//     vector<vector<int>> rides1 {{2,5,4}, {1,5,1}};
//     vector<vector<int>> rides2 {{1,5,1}, {2,5,4}};
//     vector<vector<int>> rides3 {{1,6,1}, {3,10,2}, {10,12,3}, {11,12,2}, {12,15,2}};
//     vector<vector<int>> rides4 {{1,6,1}, {3,10,2}, {10,12,3}, {11,12,2}, {12,15,2}, {13,18,1}};
//     vector<vector<int>> rides5 {{2,3,6},{8,9,8},{5,9,7},{8,9,1},{2,9,2},{9,10,6},{7,10,10},{6,7,9},{4,9,7},{2,3,1}};
//     cout << s2008.maxTaxiEarnings(10, rides1) << endl; 
//     cout << s2008.maxTaxiEarnings(10, rides2) << endl; 
//     cout << s2008.maxTaxiEarnings(10, rides3) << endl; 
//     cout << s2008.maxTaxiEarnings(10, rides4) << endl; 
//     cout << s2008.maxTaxiEarnings(10, rides5) << endl; 
// }

// void func2415(){
//     Solution2415 s2415;
//     vector<int> tree {2,3,5,8,13,21,34};

//     TreeNode* left = new TreeNode(3);
//     TreeNode* right = new TreeNode(5);
//     TreeNode* root = new TreeNode(2, left, right);

//     cout << root->val << " " << root->left->val << " " << root->right->val << endl;
//     s2415.reverseOddLevels(root);

//     // int i = 1, j=0;
//     // while (i < tree.size()){
//     //     j=i;
//     //     i = i + i*2;
//     //     for (; j < i; j+=2){
//     //         TreeNode* left = new TreeNode(tree[j]);
//     //         TreeNode* right = new TreeNode(tree[j]);

//     //     }
//     // }


// }


#include "process_comm.h"

void printNowTime(){
    time_t timep;

    time(&timep); //获取从1970至今过了多少秒，存入time_t类型的timep
    printf("%s", ctime(&timep));//用ctime将秒数转化成字符串格式，输出：Thu Feb 28 14:14:17 2019
}


int main() {

    // GetDataMethod gdm = GetDataMethod::ProcessIdMethod;
    // CommMode cm = CommMode::PipeMode;
    DataTransferFactory* dtf_ptr = new DataTransferFactory();

    // // 创建管道传输进程id的工厂
    // Transfer* ptr = dtf_ptr->getTransfer(gdm, cm);
    // ptr->send();
    // ptr->accept();

    // // 创建共享内存传输磁盘占用的工厂
    Transfer* ptr2 = dtf_ptr->getTransfer(GetDataMethod::DiskUsageMethod, CommMode::MemoryMode);
    ptr2->send();
    this_thread::sleep_for(chrono::seconds(3));
    ptr2->accept();

    // MemoryTransfer* mt_ptr_tmp = dynamic_cast<MemoryTransfer*>(ptr2);
    // mt_ptr_tmp->ClearSemAndMemory();


    return 0;
}

