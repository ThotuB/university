*version 9.1 65004552
u 38
V? 2
D? 3
R? 3
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
pageloc 1 0 2137 
@status
c 120:03:23:21:17:09;1587665829
*page 1 0 970 720 iA
@ports
port 2 AGND 200 350 h
port 36 BUBBLE 70 280 h
a 1 x 3 0 10 0 hcn 100 LABEL=vi
port 37 BUBBLE 330 280 h
a 1 x 3 0 10 0 hcn 100 LABEL=vL
@parts
part 7 r 120 280 h
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=R
a 0 xp 9 0 15 0 hln 100 REFDES=R
part 4 D1N4002 200 300 d
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=DO-41
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=D1
a 0 sp 11 0 27 4 hln 100 PART=D1N4002
a 0 ap 9 0 7 4 hln 100 REFDES=D1
part 3 VSIN 70 290 h
a 0 a 0:13 0 0 0 hln 100 PKGREF=V1
a 1 ap 9 0 20 10 hcn 100 REFDES=V1
part 6 r 330 330 v
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=RL
a 0 xp 9 0 30 25 hln 100 REFDES=RL
a 0 u 13 0 15 25 hln 100 VALUE=5k
part 5 D1N4002 260 330 v
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=DO-41
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=D2
a 0 ap 9 0 22 24 hln 100 REFDES=D2
a 0 sp 11 0 2 49 hln 100 PART=D1N4002
part 1 titleblk 970 720 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=A
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 300 95 hrn 100 PAGENO=1
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
@conn
w 25
s 200 330 200 350 24
s 70 330 70 350 26
s 70 350 200 350 28
s 200 350 260 350 30
s 330 350 330 330 31
s 260 350 330 350 35
s 260 330 260 350 33
w 9
s 70 290 70 280 8
s 70 280 120 280 10
w 13
s 330 280 330 290 14
s 160 280 200 280 16
s 260 280 330 280 20
s 260 300 260 280 18
s 200 280 260 280 23
s 200 280 200 300 21
@junction
j 70 290
+ p 3 +
+ w 9
j 120 280
+ p 7 1
+ w 9
j 330 290
+ p 6 2
+ w 13
j 160 280
+ p 7 2
+ w 13
j 260 300
+ p 5 2
+ w 13
j 260 280
+ w 13
+ w 13
j 200 300
+ p 4 1
+ w 13
j 200 280
+ w 13
+ w 13
j 200 330
+ p 4 2
+ w 25
j 200 350
+ s 2
+ w 25
j 70 330
+ p 3 -
+ w 25
j 330 330
+ p 6 1
+ w 25
j 260 330
+ p 5 1
+ w 25
j 260 350
+ w 25
+ w 25
j 70 280
+ s 36
+ w 9
j 330 280
+ s 37
+ w 13
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=A
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
