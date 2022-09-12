# 数据库操作模块

1. 接口简单，调用方便
2. 内部调用简单
3. 通用性强，覆盖myslq，sqlite3
4. 打印清晰

## 前提

1. 安装myslq和对应头文件

   ```bash
   sudo apt-get install mysql-server 
   sudo apt-get install mysql-client
   sudo apt-get install libmysqlclient-dev
   ```

2. 第一次安装mysql，新版本root用户默认使用socket，因此没有登陆权限，需要sudo进入修改配置及密码

   ```bash
   sudo mysql -u root
   ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 123456;
   sudo service mysql stop
   sudo service mysql start
   ```

## 重构想法

1. 修改接口，有些接口用不到，有些没有

   数据库封装的接口既要保证通用性，有要保证有一些特定于功能的接口，显然二者不可兼得，因此选择第一种，为了达到通用性，需要将没用的砍掉，将大接口设置成小接口。

2. 内部调用不用修改，保证每个函数只执行一个功能

3. 添加sqlite3,完善父类

4. 修改log模块位置，明确调用关系

   log模块和数据库操作模块在同一级别，只是数据库操作模块会用到log
   
5. 该模块中 使用一个全局静态变量，来作为数据库操作句柄，通过返回init的值，将生成的对象指针赋给该void指针，然后使用该指针在外层调用该模块的接口，最后调用finit函数：

   ```c++
   //销毁句柄
   ERR_CODE sdk_Finit(void* handle){
       //创建一个新的局部指针变量，并将对象指针的值赋给它
       Basic_db *phandle = reinterpret_cast<Ctmysql*>(handle);
   	phandle->Finit();
       //delete表示删除了该指针指向的值，也就是在init函数中 在堆中new出的对象的空间。
       //达到目的，删除堆内空间，将全局指针变量设置为null，且推出后栈内为空
   	delete phandle;
   	handle = NULL;
   	
   	printf("release instance success handle = %p\n", handle);
   	return ERR_SUCCESS;
   }
   ```

   因此，我们可以学习这么一种库的模式：

   **当设计api的时候，固定有两个函数入口：开始（start，init等）和结束（end，finit等）。开始函数中在堆上创建对象，结束函数中释放堆上的对象。但由于对象都是在函数内创建，因此要想在外层使用这个对象，就要有一个指针一直保存这个对象的地址，因此，必须有一个全局变量来操作。**

   也就是，api中每个函数都要传入一个保存着对象的指针，用来告知调用哪个类。有些麻烦，有没有别的做法？

   1. **尝试将全局变量放到api中，取消api函数的传入参数，app层直接调用，api层不用传参，不用返回。**

      可行！减少代码量，接口清晰！！

   
