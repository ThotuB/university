*version 9.1 1911859238
u 136
R? 8
V? 4
Q? 2
C? 4
@libraries
@analysis
.TRAN 1 0 0 0
+0 0ns
+1 4ms
+3 0.01ms
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
pageloc 1 0 5268 
@status
n 0 120:04:30:14:57:08;1590839828 e 
s 2832 120:05:02:15:19:43;1591100383 e 
*page 1 0 970 720 iA
@ports
port 10 AGND 520 430 h
port 16 AGND 620 180 h
port 102 BUBBLE 650 240 h
a 1 x 3 0 10 0 hcn 100 LABEL=Uout
port 101 BUBBLE 390 270 v
a 1 x 3 0 10 0 hcn 100 LABEL=Uin
@parts
part 13 c 410 270 h
a 0 u 13 0 10 25 hln 100 VALUE=4.7u
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=C1
a 0 ap 9 0 10 0 hln 100 REFDES=C1
part 15 c 570 240 h
a 0 x 0:13 0 0 0 hln 100 PKGREF=C2
a 0 xp 9 0 10 0 hln 100 REFDES=C2
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 u 13 0 10 25 hln 100 VALUE=4.7u
part 6 r 520 410 v
a 0 u 13 0 15 35 hln 100 VALUE=900
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=RE2
a 0 xp 9 0 25 35 hln 100 REFDES=RE2
part 7 r 460 380 v
a 0 u 13 0 15 35 hln 100 VALUE=10k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=RB2
a 0 xp 9 0 25 35 hln 100 REFDES=RB2
part 3 r 460 230 v
a 0 u 13 0 15 35 hln 100 VALUE=22k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=RB1
a 0 xp 9 0 25 35 hln 100 REFDES=RB1
part 2 r 520 230 v
a 0 u 13 0 15 35 hln 100 VALUE=2.2k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=RC
a 0 xp 9 0 25 30 hln 100 REFDES=RC
part 9 VDC 560 180 v
a 1 u 13 0 -6 8 hcn 100 DC=5V
a 0 sp 0 0 22 37 hln 100 PART=VDC
a 0 x 0:13 0 0 0 hln 100 PKGREF=EC
a 1 xp 9 0 19 7 hcn 100 REFDES=EC
part 4 r 650 360 v
a 0 u 13 0 15 30 hln 100 VALUE=10k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=RL
a 0 xp 9 0 25 30 hln 100 REFDES=RL
part 103 VSIN 390 340 h
a 1 u 13 13 45 35 hcn 100 VAMPL=20m
a 0 x 0:13 0 0 0 hln 100 PKGREF=Eg
a 1 xp 9 0 25 15 hcn 100 REFDES=Eg
a 1 u 0 0 0 0 hcn 100 VOFF=0
a 1 u 13 27 40 25 hcn 100 FREQ=1k
part 5 r 520 350 v
a 0 u 13 0 15 35 hln 100 VALUE=100
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=RE1
a 0 xp 9 0 25 35 hln 100 REFDES=RE1
part 12 Q2N2222 500 270 h
a 0 sp 11 0 25 30 hln 100 PART=Q2N2222
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=TO-18
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=Q1
a 0 ap 9 0 25 15 hln 100 REFDES=Q1
part 14 c 590 410 v
a 0 u 13 0 10 35 hln 100 VALUE=470u
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=CE
a 0 xp 9 0 20 30 hln 100 REFDES=CE
part 1 titleblk 970 720 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=A
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 300 95 hrn 100 PAGENO=1
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
@conn
w 20
a 0 up 0:33 0 0 0 hln 100 V=
s 460 230 460 270 19
s 460 270 500 270 21
s 440 270 460 270 23
s 460 270 460 340 25
a 0 up 33 0 462 305 hlt 100 V=
w 18
a 0 up 0:33 0 0 0 hln 100 V=
s 520 250 520 240 17
s 520 240 520 230 51
s 520 240 570 240 49
a 0 up 33 0 545 239 hct 100 V=
w 88
a 0 up 0:33 0 0 0 hln 100 V=
s 460 190 460 180 87
s 460 180 520 180 89
a 0 up 33 0 490 179 hct 100 V=
s 520 180 560 180 93
s 520 180 520 190 91
w 95
a 0 up 0:33 0 0 0 hln 100 V=
s 600 180 620 180 94
a 0 up 33 0 610 179 hct 100 V=
w 53
a 0 up 0:33 0 0 0 hln 100 V=
s 600 240 650 240 52
s 650 240 650 320 54
a 0 up 33 0 652 280 hlt 100 V=
w 106
a 0 up 0:33 0 0 0 hln 100 V=
s 520 420 460 420 56
s 460 420 460 380 58
s 520 410 520 420 34
s 520 420 520 430 38
s 520 420 590 420 36
s 590 420 590 410 39
s 590 420 650 420 41
s 650 420 650 360 43
s 460 420 390 420 60
a 0 up 33 0 425 419 hct 100 V=
s 390 420 390 380 62
w 69
a 0 up 0:33 0 0 0 hln 100 V=
s 390 270 410 270 109
s 390 340 390 270 64
a 0 up 33 0 392 305 hlt 100 V=
w 33
a 0 up 0:33 0 0 0 hln 100 V=
s 520 310 520 290 126
w 121
a 0 up 0:33 0 0 0 hln 100 V=
s 520 350 520 360 83
a 0 up 33 0 522 360 hlt 100 V=
s 520 360 520 370 133
s 520 360 590 360 131
s 590 360 590 380 134
@junction
j 520 230
+ p 2 1
+ w 18
j 520 250
+ p 12 c
+ w 18
j 500 270
+ p 12 b
+ w 20
j 440 270
+ p 13 2
+ w 20
j 460 270
+ w 20
+ w 20
j 460 340
+ p 7 2
+ w 20
j 570 240
+ p 15 1
+ w 18
j 520 240
+ w 18
+ w 18
j 600 240
+ p 15 2
+ w 53
j 650 320
+ p 4 2
+ w 53
j 410 270
+ p 13 1
+ w 69
j 520 350
+ p 5 1
+ w 121
j 520 370
+ p 6 2
+ w 121
j 460 230
+ p 3 1
+ w 20
j 460 190
+ p 3 2
+ w 88
j 560 180
+ p 9 +
+ w 88
j 520 190
+ p 2 2
+ w 88
j 520 180
+ w 88
+ w 88
j 600 180
+ p 9 -
+ w 95
j 620 180
+ s 16
+ w 95
j 650 240
+ s 102
+ w 53
j 390 340
+ p 103 +
+ w 69
j 390 270
+ s 101
+ w 69
j 590 410
+ p 14 1
+ w 106
j 520 410
+ p 6 1
+ w 106
j 520 430
+ s 10
+ w 106
j 520 420
+ w 106
+ w 106
j 590 420
+ w 106
+ w 106
j 650 360
+ p 4 1
+ w 106
j 460 380
+ p 7 1
+ w 106
j 460 420
+ w 106
+ w 106
j 390 380
+ p 103 -
+ w 106
j 520 310
+ p 5 2
+ w 33
j 520 290
+ p 12 e
+ w 33
j 520 360
+ w 121
+ w 121
j 590 380
+ p 14 2
+ w 121
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=A
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
