# DES算法实现    

## 一、DES算法原则
&emsp;DES设计中使用了分组密码设计的两个原则：混淆（confusion）和扩散(diffusion)，其目的是抗击敌手对密码系统的统计分析。混淆是使密文的统计特性与密钥的取值之间的关系尽可能复杂化，以使密钥和明文以及密文之间的依赖性对密码分析者来说是无法利用的。扩散的作用就是将每一位明文的影响尽可能迅速地作用到较多的输出密文位中，以便在大量的密文中消除明文的统计结构，并且使每一位密钥的影响尽可能迅速地扩展到较多的密文位中，以防对密钥进行逐段破译。    

## 二、DES算法步骤

![image](https://user-images.githubusercontent.com/43472106/156557124-10eb7997-3c44-4131-a99e-0576a8460836.png)

## 三、实现过程
&emsp;见DES.cpp源文件

## 四、编译运行     
   ### 1、主函数展示如下图：       

![image](https://user-images.githubusercontent.com/43472106/156356775-a507be62-4a3f-456e-b470-5ac0f5a4866e.png)

   ### 2、linux下编译     

![image](https://user-images.githubusercontent.com/43472106/156357289-c153a355-4a31-42ea-914d-c1bc68029814.png)

   ### 3、编译结果    

![image](https://user-images.githubusercontent.com/43472106/156357392-f7f14b35-10c7-4fa3-8c77-6ddb46a7aeb6.png)    

&emsp;注：eText为加密后的密文，是一段01字符串；dText为解密后的密文，与上文message对应。   
    
     

#### *该算法是我在大三上学期所上课程《信息安全》所实现的任务，文中注释是后加的。*
