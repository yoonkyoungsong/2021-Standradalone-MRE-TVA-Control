%%
clear all; close all; clc;

fs=2000;
runningTime=100;

num=1;

titleName1 = sprintf("retune_time_Vmre_Vfft_%d.txt",num);
titleName2 = sprintf("retune_time_freq_step_%d.txt",num); 
titleName3 = sprintf("retune_time_Vaccin_Vaccout_%d.txt",num);

data1=load(titleName1);
data2=load(titleName2); 
data3=load(titleName3);

ts_Vmre = 0.0005;
ts_acc = 0.0005;
ts_ctrl = 0.5120;

t_Vmre = data1(:,1);
t_ctrl = data2(:,1);
t_acc = data3(:,1);

in_acc = data3(:,2);
out_acc = data3(:,3);

B_ctrl = data2(:,3);
freq_ctrl = data2(:,2);
Vmre = data1(:,2);

Vmref=bandpass(Vmre,[30 60],fs);

inout_acc=accNorm(in_acc, out_acc);
inout_Vmref=accNorm(in_acc, Vmref);

% figure()
% plot(t_acc-10, in_acc)
% % hold on
% % plot(t_acc, out_acc)
% xlim([0 90])

figure()
subplot(2,1,1)
plot(t_acc-10, inout_acc)
xlim([0 90])
legend('ACC')
xlabel("Time[s]")
ylabel("Target  Plant Acc[g]")

subplot(2,1,2)
plot(t_Vmre-10, inout_Vmref)
xlim([0 90])
legend('Vmre')
xlabel("Time[s]")
ylabel("MRE Maginitude[V]")



