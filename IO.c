#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main()
{
    //mode_t umask(mode_t mask);
    //将当前进程的文件创建权限掩码修改成为mask
    umask(0);
    //int open(const char* pathname,int flags,mode_t mode);
    int fd=open("./test.txt",O_RDWR|O_CREAT|O_APPEND|O_TRUNC,0664);
    if(fd<0)
    {
        perror("open error");
        return -1;
    }

    //ssize_t write(int fd,const void* buf,size_t count);
    //fd:open打开文件所返回的文件描述符
    //buf:要写入的数据
    //count:要写入的字节数
    //返回值：实际写入的字节数    失败：-1
    char* data="jintian zhouyi!\n";
    ssize_t ret=write(fd,data,strlen(data));
    if(ret<0){
        perror("write error");
        return -1;
    }
    //off_t lseek(int fd,off_t offset,int whence);
    //跳转fd文件的读写位置到指定处
    //whence:SEEK_SET     SEEK_CUR   SEEK_END
    //offset:偏移量
    lseek(fd,0,SEEK_SET);

    //ssize_t read(int fd,void* buf,size_t count);
    //从fd文件中读取count长度的数据，放到buf中
    //返回值：实际读到的字节数    失败：-1
    char buf[1024]={0};
    ret=read(fd,buf,1023);
    if(ret<0){
        perror("read error");
        return -1;
    }
    printf("ret:%d-[%s]\n",ret,buf);

    //int close(int fd);
    close(fd);
    return 0;
}
