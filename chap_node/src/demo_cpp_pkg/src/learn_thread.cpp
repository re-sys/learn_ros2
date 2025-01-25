#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include "cpp-httplib/httplib.h"

class Download{
    public:
        void download(const std::string& host,const std::string& path,const std::function<void(const std::string&, const std::string&)>& callback){
            std::cout << "Downloading " <<host<< 
            "thread id: " << std::this_thread::get_id() << std::endl;
            httplib::Client cli(host);
            auto res = cli.Get(path);
            if (res && res->status == 200) {
                
                callback(path, res->body);
            } else {
                std::cout << "Error: " << res.error() << std::endl;
            }
        }
        void start_download(const std::string& host, const std::string& path, const std::function<void(const std::string&, const std::string&)>& callback)
        {
            auto download_func = std::bind(&Download::download, this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
            std::thread thread(download_func,host,path,callback);
            thread.detach();
            
        }
};

int main() {
       auto d = Download();
       auto word_counter = [](const std::string& path, const std::string& body)->void {
           std::cout << "Word count for " << path << " is " << body.size() << 
           " and the first word is " << body.substr(0, 9) << std::endl;
       };
       d.start_download("http://0.0.0.0:8000","/novel1.txt",word_counter);
       d.start_download("http://0.0.0.0:8000","/novel3.txt",word_counter);
       d.start_download("http://0.0.0.0:8000","/novel2.txt",word_counter);
       std::this_thread::sleep_for(std::chrono::seconds(10));
       return 0;
}


