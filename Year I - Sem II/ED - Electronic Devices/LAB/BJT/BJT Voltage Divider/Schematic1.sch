*version 9.1 2970795943
u 58
Q? 2
R? 5
V? 2
@libraries
@analysis
@targets
@attributes
@translators
a 0 u 13 0 0 0 hln 100 PCBOARDS=PCB
a 0 u 13 0 0 0 hln 100 PSPICE=PSPICE
a 0 u 13 0 0 0 hln 100 XILINX=XILINX
@setup
unconnectedPins 0
connectViaLabel 0
connectViaLocalLabels 0
NoStim4ExtIFPortsWarnings 1
AutoGenStim4ExtIFPorts 1
@index
pageloc 1 0 3021 
@status
c 120:04:28:06:08:57;1590635337
n 0 120:04:28:06:13:49;1590635629 e 
s 2832 120:04:28:06:13:52;1590635632 e 
*page 1 0 970 720 iA
@ports
port 52 AGND 550 430 h
port 57 BUBBLE 460 320 v
a 1 x 3 0 10 0 hcn 100 LABEL=VB
port 53 BUBBLE 550 290 d
a 1 x 3 0 10 -10 hcn 100 LABEL=VC
port 55 BUBBLE 550 350 d
a 1 x 3 0 10 -10 hcn 100 LABEL=VE
@parts
part 7 VDC 640 300 h
a 0 sp 0 0 22 37 hln 100 PART=VDC
a 0 x 0:13 0 0 0 hln 100 PKGREF=EC
a 1 xp 9 0 24 7 hcn 100 REFDES=EC
a 1 u 13 0 24 33 hcn 100 DC=12V
part 3 r 550 280 v
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=RC
a 0 xp 9 0 25 35 hln 100 REFDES=RC
a 0 u 13 0 10 40 hln 100 VALUE=2.2k
part 6 r 550 400 v
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=RE
a 0 xp 9 0 25 35 hln 100 REFDES=RE
a 0 u 13 0 10 30 hln 100 VALUE=1k
part 2 Q2N2222 530 320 h
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=TO-18
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=Q1
a 0 ap 9 0 25 15 hln 100 REFDES=Q1
a 0 sp 11 0 25 30 hln 100 PART=Q2N2222
part 4 r 460 280 v
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=RB1
a 0 xp 9 0 25 40 hln 100 REFDES=RB1
a 0 u 13 0 10 40 hln 100 VALUE=47k
part 5 r 460 400 v
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=RB2
a 0 xp 9 0 25 40 hln 100 REFDES=RB2
a 0 u 13 0 10 35 hln 100 VALUE=20k
part 1 titleblk 970 720 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=A
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
a 1 s 13 0 300 95 hrn 100 PAGENO=1
@conn
w 37
a 0 up 0:33 0 0 0 hln 100 V=
s 460 210 550 210 10
s 640 210 640 300 16
s 550 210 640 210 42
a 0 up 33 0 595 209 hct 100 V=
s 550 210 550 240 12
s 460 240 460 210 8
w 19
a 0 up 0:33 0 0 0 hln 100 V=
s 640 430 550 430 24
s 640 340 640 430 18
s 460 430 460 400 26
s 550 430 460 430 50
a 0 up 33 0 505 429 hct 100 V=
s 550 430 550 400 22
w 36
a 0 up 0:33 0 0 0 hln 100 V=
s 550 280 550 290 40
s 550 290 550 300 54
a 0 up 33 0 552 295 hlt 100 V=
w 34
a 0 up 0:33 0 0 0 hln 100 V=
s 550 360 550 350 48
s 550 350 550 340 56
a 0 up 33 0 552 345 hlt 100 V=
w 29
a 0 up 0:33 0 0 0 hln 100 V=
s 530 320 460 320 30
a 0 up 33 0 495 319 hct 100 V=
s 460 320 460 280 32
s 460 360 460 320 28
@junction
j 640 300
+ p 7 +
+ w 37
j 640 340
+ p 7 -
+ w 19
j 550 240
+ p 3 2
+ w 37
j 550 210
+ w 37
+ w 37
j 550 280
+ p 3 1
+ w 36
j 460 280
+ p 4 1
+ w 29
j 460 240
+ p 4 2
+ w 37
j 460 400
+ p 5 1
+ w 19
j 460 360
+ p 5 2
+ w 29
j 460 320
+ w 29
+ w 29
j 550 400
+ p 6 1
+ w 19
j 550 430
+ w 19
+ w 19
j 550 360
+ p 6 2
+ w 34
j 550 430
+ s 52
+ w 19
j 550 290
+ s 53
+ w 36
j 550 350
+ s 55
+ w 34
j 460 320
+ s 57
+ w 29
j 530 320
+ p 2 b
+ w 29
j 550 300
+ p 2 c
+ w 36
j 550 340
+ p 2 e
+ w 34
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=A
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
