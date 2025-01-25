import threading
import requests

class DownLoad:
    def download(self, url,callback):
        print(f"init {url}")
        response = requests.get(url)
        response.encoding = 'utf-8'
        callback(url,response.text)
    def start_download(self,url,callback):
        thread = threading.Thread(target=self.download, args=(url,callback))
        thread.start()
    
def word_count(url,result):
    """
    下载网页内容并统计字数
    """
    print(f"{url}:{len(result)}->{result[:1]}")

def main():
    download = DownLoad()
    download.start_download("http://0.0.0.0:8000/novel1.txt",word_count)
    download.start_download("http://0.0.0.0:8000/novel2.txt",word_count)
    download.start_download("http://0.0.0.0:8000/novel3.txt",word_count)
    
    
