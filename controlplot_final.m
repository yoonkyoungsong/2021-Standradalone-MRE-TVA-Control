%% input output 동시 data load

clear all; clc;

runningTime=300;
num=1;

fstart=35;
ffinal=50;
T=30;
% 
titleName1 = sprintf("nonControl_time_Vmre_Vfft_%d.txt",num);
titleName2 = sprintf("nonControl_time_freq_step_%d.txt",num);
titleName3 = sprintf("nonControl_time_Vaccin_Vaccout_%d.txt",num);

% titleName1 = sprintf("nonControl_time_Vmre_Vmref_%d.txt",num);
% titleName2 = sprintf("nonControl_time_freq_step_%d.txt",num);
% titleName3 = sprintf("nonControl_time_Vacc_%d.txt",num);
% titleName3 = sprintf("in_nonControl_time_Vaccin_Vaccout_%d.txt",num);

titleName4 = sprintf("Control_time_Vmre_Vfft_%d.txt",num);
titleName5 = sprintf("Control_time_freq_step_%d.txt",num);
titleName6 = sprintf("Control_time_Vaccin_Vaccout_%d.txt",num);

% titleName4 = sprintf("MAXControl_time_Vmre_Vmref_%d.txt",num);
% titleName5 = sprintf("MAXControl_time_freq_step_%d.txt",num);
% titleName6 = sprintf("MAXControl_time_Vacc_%d.txt",num);
% titleName6 = sprintf("in_MAXControl_time_Vaccin_Vaccout_%d.txt",num);


data1=load(titleName1);
data2=load(titleName2); 
data3=load(titleName3);
data4=load(titleName4);
data5=load(titleName5);
data6=load(titleName6);


ts_Vmre = 0.0005;
ts_acc = 0.0005;
ts_ctrl = 0.5120;

t_Vmre = data4(:,1);
t_ctrl = data5(:,1);
t_acc = data6(:,1);

in_acc_nonctrl = data3(:,2);
in_acc_ctrl = data6(:,2);
out_acc_nonctrl = data3(:,3);
out_acc_ctrl = data6(:,3);

B_ctrl = data5(:,3);
freq_ctrl = data5(:,2);
Vmre_nonctrl = data1(:,2);
Vmre_ctrl = data4(:,2);


% 주파수 추정 / 외부 자기장 / 가속도계 / MRE 전압 
clc

N_acc_nonctrl = length(out_acc_nonctrl);
N_acc_ctrl = length(out_acc_ctrl);
N_B_ctrl = length(B_ctrl);
N_freq_ctrl = length(freq_ctrl);
N_Vmre_nonctrl = length(Vmre_ctrl);
N_Vmre_ctrl = length(Vmre_ctrl);

% inout_acc_nonctrl=accNorm(in_acc_nonctrl, out_acc_nonctrl);
% inout_acc_ctrl=accNorm(in_acc_ctrl,out_acc_ctrl);
% 
% inout_Vmre_nonctrl=accNorm(in_acc_nonctrl, Vmre_nonctrl);
% inout_Vmre_ctrl=accNorm(in_acc_ctrl,Vmre_ctrl);


fin = fstart:0.5:ffinal;
fin = [fin fin fin fin fin fin fin fin fin fin];
t_fin = 0:T;
t_fin = [t_fin t_fin+T t_fin+2*T t_fin+3*T t_fin+4*T t_fin+5*T t_fin+6*T t_fin+7*T t_fin+8*T t_fin+9*T];

YColor = [0.97,0.8,0.01];
GColor = [0.5, 0.5, 0.5];


figure()
hold on

subplot(4,1,1)
plot(t_ctrl(1:N_freq_ctrl)-60.5+0.2784,freq_ctrl,'color', YColor,'linewidth',1.5);
hold on
plot(t_fin-60.5, fin,'--','color', [0.5, 0.5, 0.5],'linewidth',1.5);
xlim([0 runningTime])
xlim([0  90])
ylim([25 60])
xlabel("Time[s]")
ylabel("Frequency[Hz]")
legend('Estimated','Reference')

subplot(4,1,2)
plot(t_ctrl(1:N_B_ctrl)-90.5+0.2784, B_ctrl,'color',YColor,'linewidth',1.5);
hold on
plot([0 300], [0,0],'color', GColor,'linewidth',1.5);
xlim([0 runningTime]);
xlim([0  90])
ylim([-1 8])
xlabel("Time[s]")
ylabel("Magnetic Field[mT]")
legend('Controlled','Uncontrolled')

subplot(4,1,3)
plot(t_acc(1:N_acc_nonctrl)-60.5, out_acc_nonctrl(1:N_acc_nonctrl),'color', GColor,'linewidth',1.5);
hold on
plot((t_acc(1:N_acc_ctrl))-60.5+0.2784, out_acc_ctrl(1:N_acc_nonctrl),'color', YColor,'linewidth',1.5);
xlim([0 runningTime]);
xlim([0  90])
ylim([-0.4 0.4])
xlabel("Time[s]")
ylabel("Target  Plant Acc[g]")
legend('Uncontrolled','Controlled')
%-0.8561 2월 2일 2번 
%-0.3858 2월 22일 0번
% +0.4994 2월 22일 1번

% subplot(4,1,4);
% plot(t_Vmre(1:N_Vmre_ctrl), inout_Vmre_ctrl,'color',YColor);
% hold on
% plot(t_Vmre(1:N_Vmre_nonctrl), inout_Vmre_nonctrl,'color', GColor);
% xlim([0 runningTime]);
% ylim([-0.5 0.5])
% xlabel("Time[s]")
% ylabel("MRE Maginitude[V]")
% legend('Controlled','Uncontrolled')


fs=2000;
Vmref_ctrl=bandpass(Vmre_ctrl,[30 60],fs);
Vmref_nonctrl=bandpass(Vmre_nonctrl,[30 60],fs);

% inout_Vmref_nonctrl=accNorm(in_acc_nonctrl, Vmref_nonctrl);
% inout_Vmref_ctrl=accNorm(in_acc_ctrl,Vmref_ctrl);

%figure()
subplot(4,1,4);
plot(t_Vmre(1:N_Vmre_ctrl)-60.5+0.2784, Vmref_ctrl,'color',YColor,'linewidth',1.5);
hold on
plot(t_Vmre(1:N_Vmre_nonctrl)-60.5, Vmref_nonctrl,'color', GColor,'linewidth',1.5);
xlim([0 runningTime]);
xlim([0  90])
%ylim([-2 2])
xlabel("Time[s]")
ylabel("MRE Maginitude[V]")
legend('Controlled','Uncontrolled')

 
% subplot(5,1,5);
% plot(t_Vmre(1:N_Vmre_ctrl), inout_Vmref_ctrl,'color',YColor);
% hold on
% plot(t_Vmre(1:N_Vmre_nonctrl), inout_Vmref_nonctrl,'color', GColor);
% xlim([0 runningTime]);
% %ylim([-0.5 0.5])
% xlabel("Time[s]")
% ylabel("MRE Maginitude[V]")
% legend('Controlled','Uncontrolled')


%% filter 전 MRE 전압

figure()
plot(t_Vmre(1:N_Vmre_ctrl), Vmre_ctrl,'color',YColor);
hold on
plot(t_Vmre(1:N_Vmre_nonctrl), Vmre_nonctrl,'color', GColor);
xlim([0 runningTime]);
%ylim([-2 2])
xlabel("Time[s]")
ylabel("MRE Maginitude[V]")
legend('Controlled','Uncontrolled')

%% acc input
figure()
plot(t_acc(1:N_acc_nonctrl), in_acc_nonctrl(1:N_acc_nonctrl),'color', GColor);
hold on
plot((t_acc(1:N_acc_ctrl)), in_acc_ctrl(1:N_acc_nonctrl),'color', YColor);
xlim([0 runningTime]);
ylim([-0.5 0.5])
xlabel("Time[s]")
ylabel("Target  Plant Acc[g]")
legend('Uncontrolled','Controlled')

%% mre 신호 band pass filter + /input norm
fs=2000;
% Vmref_ctrl=bandpass(Vmre_ctrl,[30 60],fs);
% Vmref_nonctrl=bandpass(Vmre_nonctrl,[30 60],fs);

inout_Vmre_nonctrl=accNorm(in_acc_nonctrl, Vmre_nonctrl);
inout_Vmre_ctrl=accNorm(in_acc_ctrl,Vmre_ctrl);

figure()
subplot(2,1,1);
plot(t_Vmre(1:N_Vmre_ctrl), Vmre_ctrl,'color',YColor);
hold on
plot(t_Vmre(1:N_Vmre_nonctrl), Vmre_nonctrl,'color', GColor);
xlim([0 runningTime]);
%ylim([-2 2])
xlabel("Time[s]")
ylabel("MRE Maginitude[V]")
legend('Controlled','Uncontrolled')


subplot(2,1,2);
plot(t_Vmre(1:N_Vmre_ctrl), inout_Vmre_ctrl,'color',YColor);
hold on
plot(t_Vmre(1:N_Vmre_nonctrl), inout_Vmre_nonctrl,'color', GColor);
xlim([0 runningTime]);
%ylim([-0.5 0.5])
xlabel("Time[s]")
ylabel("MRE Maginitude[V]")
legend('Controlled','Uncontrolled')

%% control 반대

N_acc_nonctrl = length(out_acc_nonctrl);
N_acc_ctrl = length(out_acc_ctrl);
N_B_ctrl = length(B_ctrl);
N_freq_ctrl = length(freq_ctrl);
N_Vmre_nonctrl = length(Vmre_ctrl);
N_Vmre_ctrl = length(Vmre_ctrl);


fs=2000;
Vmref_ctrl=bandpass(Vmre_ctrl,[30 60],fs);
Vmref_nonctrl=bandpass(Vmre_nonctrl,[30 60],fs);

inout_Vmre_nonctrl=accNorm(in_acc_nonctrl, Vmref_nonctrl);
inout_Vmre_ctrl=accNorm(in_acc_ctrl,Vmref_ctrl);



inout_acc_nonctrl=accNorm(in_acc_nonctrl, out_acc_nonctrl);
inout_acc_ctrl=accNorm(in_acc_ctrl,out_acc_ctrl);



fin = 30:55;  
fin = [fin fin fin fin fin fin fin fin fin fin];
t_fin = 0:25;
t_fin = [t_fin t_fin+25 t_fin+50 t_fin+75 t_fin+100 t_fin+125 t_fin+150 t_fin+175 t_fin+200 t_fin+225];

YColor = [0.97,0.8,0.01];
GColor = [0.5, 0.5, 0.5];


figure()
hold on

subplot(4,1,1)
plot(t_fin, fin,'--','color', [0.5, 0.5, 0.5])
hold on
plot(t_ctrl(1:N_freq_ctrl),freq_ctrl,'color', YColor,'linewidth',1.3)
xlim([0 runningTime])
ylim([25 60])
xlabel("Time[s]")
ylabel("Frequency[Hz]")
legend('Reference','Estimated')

subplot(4,1,2)
plot(t_ctrl(1:N_B_ctrl), B_ctrl,'color',YColor,'linewidth',1.3);
hold on
plot([0 200], [0,0],'color', GColor);
xlim([0 runningTime]);
ylim([0 8])
xlabel("Time[s]")
ylabel("Magnetic Field[mT]")
legend('Controlled','Uncontrolled')

subplot(4,1,3)
plot((t_acc(1:N_acc_ctrl)), inout_acc_ctrl(1:N_acc_nonctrl),'color', YColor);
hold on
plot(t_acc(1:N_acc_nonctrl), inout_acc_nonctrl(1:N_acc_nonctrl),'color', GColor);
xlim([0 runningTime]);
ylim([-0.1 0.1])
xlabel("Time[s]")
ylabel("Target  Plant Acc[g]")
legend('Uncontrolled','Controlled')
%-0.8561 2월 2일 2번 
%-0.3858 2월 22일 0번
% +0.4994 2월 22일 1번

subplot(4,1,4);
plot(t_Vmre(1:N_Vmre_nonctrl), inout_Vmre_nonctrl,'color', GColor);
hold on
plot(t_Vmre(1:N_Vmre_ctrl), inout_Vmre_ctrl,'color',YColor);
xlim([0 runningTime]);
ylim([-1 1])
xlabel("Time[s]")
ylabel("MRE Sensor Voltage[V]")
legend('Controlled','Uncontrolled')


%% 필터 전 후 MRE 전압 크기

Vmre_0mT = data4(:,2);
Vmre_ctrl = data1(:,2);

subplot(2,1,1);
plot(t_Vmre(1:N_Vmre_ctrl)-0.3084, Vmre_ctrl,'color',YColor);
hold on
plot(t_Vmre(1:N_Vmre_nonctrl), Vmre_0mT,'color', GColor);
xlim([0 runningTime]);
%ylim([-1.5 1.5])
xlabel("Time[s]")
ylabel("MRE Maginitude[V]")
legend('Controlled','Uncontrolled')

Vmre_0mT = data4(:,3);
Vmre_ctrl = data1(:,3);

subplot(2,1,2);
plot(t_Vmre(1:N_Vmre_ctrl)-0.3084, Vmre_ctrl,'color',YColor);
hold on
plot(t_Vmre(1:N_Vmre_nonctrl), Vmre_0mT,'color', GColor);
xlim([0 runningTime]);
%ylim([-1.5 1.5])
xlabel("Time[s]")
ylabel("MRE Maginitude[V]")
legend('Controlled','Uncontrolled')



%% input output 별개 data load
clear all; clc;

runningTime=250;

num=0;

titleName1 = sprintf("in_nonControl_time_Vmre_Vmref_%d.txt",num);
titleName2 = sprintf("in_nonControl_time_freq_step_%d.txt",num);
titleName3 = sprintf("in_nonControl_time_Vacc_%d.txt",num);

titleName4 = sprintf("in_Control_time_Vmre_Vmref_%d.txt",num);
titleName5 = sprintf("in_Control_time_freq_step_%d.txt",num);
titleName6 = sprintf("in_Control_time_Vacc_%d.txt",num);

titleName7 = sprintf("out_nonControl_time_Vmre_Vmref_%d.txt",num);
titleName8 = sprintf("out_nonControl_time_freq_step_%d.txt",num);
titleName9 = sprintf("out_nonControl_time_Vacc_%d.txt",num);

titleName10 = sprintf("out_Control_time_Vmre_Vmref_%d.txt",num);
titleName11 = sprintf("out_Control_time_freq_step_%d.txt",num);
titleName12 = sprintf("out_Control_time_Vacc_%d.txt",num);



data1=load(titleName1);
data2=load(titleName2); 
data3=load(titleName3);
data4=load(titleName4);
data5=load(titleName5);
data6=load(titleName6);

data7=load(titleName7);
data8=load(titleName8); 
data9=load(titleName9);
data10=load(titleName10);
data11=load(titleName11);
data12=load(titleName12);

ts_Vmre = 0.0005;
ts_acc = 0.0005;
ts_ctrl = 0.5120;

t_Vmre = data10(:,1);
t_ctrl = data11(:,1);
t_acc = data12(:,1);

in_acc_nonctrl = data3(:,2);
in_acc_ctrl = data6(:,2);
out_acc_nonctrl = data9(:,2);
out_acc_ctrl = data12(:,2);

B_ctrl = data11(:,3);
freq_ctrl = data11(:,2);
Vmre_nonctrl = data7(:,2);
Vmre_ctrl = data10(:,2);


