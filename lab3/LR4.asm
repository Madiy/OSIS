.model small 
.stack 1000 
.data 
old dd 0 
sss db 256 dup('$') 
vOldInt LABEL WORD 
.code 
.486 

new_handle proc 
push ds si es di dx cx bx ax 


xor ax, ax 
in al, 60h 

cmp al, 39h
je exit

jmp old_handler 

old_handler: 
pop ax bx cx dx di es si ds 
jmp dword ptr cs:old ;вызов стандартного обработчика прерывания 
xor ax, ax 
mov al, 20h 
out 20h, al 

exit: 
xor ax, ax 
mov al, 20h 
out 20h, al 
pop ax bx cx dx di es si ds ;восстановление регистров перед выходом из нашего обработчика прерываний 
iret
new_handle endp 


new_end: 

start: 
mov ax, @data 
mov ds, ax 

cli ;сброс флага IF 
pushf 
push 0 ;перебрасываем значение 0 в DS 
pop ds 
mov eax, ds:[09h*4] 
mov cs:[old], eax ;сохранение системного обработчика 

mov ax, cs 
shl eax, 16 
mov ax, offset new_handle 
mov ds:[09h*4], eax ;запись нового обработчика 
sti ;Установка флага IF 

xor ax, ax 
mov ah, 31h 
MOV DX, (New_end - @code + 10FH) / 16 ;вычисление размера резидентной части в параграфах(16 байт) 
INT 21H 



end start