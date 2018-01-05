%%MQAM system
clc
clear all
close all
%% Theoretical curve
figure
n0=(1e-6); 
% xdBm=linspace(-120,-50,1000);
% x=(10.^(xdBm./10))/1000;
% func=erfc(sqrt(x/(2*n0)));
% 
% plot(x,func)
% grid on
EbNodBm=linspace(-160,-20,1000);
EbNo=(1e3)*(1e-3)*(10.^(EbNodBm/10));%the first factor is the amplification of the signal
%the second is the conversion to mWatt
%k=2;
%M=2^k;
%x=sqrt(3*k*EbNo/(M-1));
Pb=0.5*erfc(sqrt(2*EbNo/n0));
%Pb=(4/k)*(1-(1/sqrt(M)))*(1/2)*erfc(x/sqrt(2*n0));
x=EbNo/n0;
semilogy(sqrt(x),Pb,'LineWidth',1.5)
grid on
set(gca, 'YScale', 'log')
axis([0 1.6 1e-3 1e0])
xlabel('$\sqrt{E_b/n_0}$','Interpreter','Latex')
ylabel('BER','Interpreter','Latex')
leg=legend('QPSK theoretical curve');
set(leg,'position',[0.2 0.18 0.2964 0.0869],'FontSize',12,'Interpreter','Latex')
ax=gca;
ax.LineWidth=1.2;
ax.FontSize=12;
%% BER parameters: amp=10e3, noise_amp=10e-6, LO_power=0dBm, n_bits=200
figure
A=importdata('BER.txt');
NumLin=size(A,1);
OpticalPower=A(1:NumLin,1);
ber=A(1:NumLin,2);
Up=A(1:NumLin,3);
Lo=A(1:NumLin,4);
yneg=ber-Lo;
ypos=Up-ber;
errorbar(OpticalPower,ber,yneg,ypos,'b*')
grid on
xlabel('Output optical power (dBm)')
ylabel('BER')
axis([-120 -50 -.05 .35])
%% BER parameters: amp=10e3, noise_amp=10e-6, LO_power=0dBm, n_bits=1000, buffer_length=512
figure
A=importdata('BER2.txt');
NumLin=size(A,1);
OpticalPower=A(1:NumLin,1);
ber=A(1:NumLin,2);
Up=A(1:NumLin,3);
Lo=A(1:NumLin,4);
yneg=ber-Lo;
ypos=Up-ber;
errorbar(OpticalPower,ber,yneg,ypos,'b*')
grid on
xlabel('Output optical power (dBm)')
ylabel('BER')
hold on
%plot(EbNodB,Pb)
%% BER parameters: amp=10e3, noise_amp=10e-6, LO_power=0dBm, n_bits=4000, buffer_length=512, bits: 01000...
figure
A=importdata('BER3.txt');
NumLin=size(A,1);
OpticalPower=A(1:NumLin,1);
ber=A(1:NumLin,2);
Up=A(1:NumLin,3);
Lo=A(1:NumLin,4);
yneg=ber-Lo;
ypos=Up-ber;
errorbar(OpticalPower,ber,yneg,ypos,'b*')
grid on
xlabel('Output optical power (dBm)')
ylabel('BER')
hold on
%plot(EbNodB,Pb)
%% BER parameters: amp=10e3, noise_amp=10e-6, LO_power=0dBm, n_bits=4000, buffer_length=512, bits: random
figure
A=importdata('BER4.txt');
NumLin=size(A,1);
OpticalPower=A(1:NumLin,1);
ber=A(1:NumLin,2);
Up=A(1:NumLin,3);
Lo=A(1:NumLin,4);
yneg=ber-Lo;
ypos=Up-ber;
errorbar(OpticalPower,ber,yneg,ypos,'bs','MarkerSize',5,'MarkerFaceColor','b')
grid on
xlabel('Output optical power (dBm)')
ylabel('BER')
hold on
plot(EbNodBm,Pb,'r','LineWidth',1.5)
set(gca, 'YScale', 'log')
legend('Simulation results','QPSK theoretical curve')
title('Random')
%% BER parameters: amp=10e3, noise_amp=10e-6, LO_power=0dBm, n_bits=4000, buffer_length=512, bits: 010101... (deterministic cyclic)
figure
A=importdata('BER5.txt');
NumLin=size(A,1);
OpticalPower=A(1:NumLin,1);
ber=A(1:NumLin,2);
Up=A(1:NumLin,3);
Lo=A(1:NumLin,4);
yneg=ber-Lo;
ypos=Up-ber;
errorbar(OpticalPower,ber,yneg,ypos,'bs','MarkerSize',5,'MarkerFaceColor','b')
grid on
xlabel('Output optical power (dBm)')
ylabel('BER')
hold on
plot(EbNodBm,Pb,'r','LineWidth',1.5)
legend('Simulation results','QPSK theoretical curve')
title('Deterministic Cyclic 0101...')
%% BER parameters: amp=10e3, noise_amp=10e-6, LO_power=0dBm, n_bits=4000, buffer_length=512, bits: Pseudorandom sequence 2^7
figure
A=importdata('BER6.txt');
NumLin=size(A,1);
OpticalPower_dBm=A(1:NumLin,1);
OpticalPower=(1e3)*(1e-3)*(10.^(OpticalPower_dBm/10));
xExp=OpticalPower/n0;
ber=A(1:NumLin,2);
Up=A(1:NumLin,3);
Lo=A(1:NumLin,4);
yneg=ber-Lo;
ypos=Up-ber;
errorbar(sqrt(xExp),ber,yneg,ypos,'bs','MarkerSize',5,'MarkerFaceColor','b')
grid on
xlabel('$\sqrt{E_b/n_0}$','Interpreter','Latex')
ylabel('BER','Interpreter','Latex')
hold on
plot(sqrt(EbNo/n0),Pb,'r','LineWidth',1.5)
set(gca, 'YScale', 'log')
leg=legend('Simulation results','QPSK theoretical curve');
set(leg,'position',[0.2 0.18 0.2964 0.0869],'FontSize',12,'Interpreter','Latex')
%title('Pseudorandom sequence 2^7')
axis([0 1.6 1e-3 1e0])
ax=gca;
ax.LineWidth=1.2;
ax.FontSize=12;
%% only simulation
figure
A=importdata('BER6.txt');
NumLin=size(A,1);
OpticalPower_dBm=A(1:NumLin,1);
OpticalPower=(1e3)*(1e-3)*(10.^(OpticalPower_dBm/10));
xExp=OpticalPower/n0;
ber=A(1:NumLin,2);
Up=A(1:NumLin,3);
Lo=A(1:NumLin,4);
yneg=ber-Lo;
ypos=Up-ber;
errorbar(sqrt(xExp),ber,yneg,ypos,'bs','MarkerSize',5,'MarkerFaceColor','b')
grid on
xlabel('$\sqrt{E_b/n_0}$','Interpreter','Latex')
ylabel('BER','Interpreter','Latex')
set(gca, 'YScale', 'log')
leg=legend('Simulation results');
set(leg,'position',[0.2 0.18 0.2964 0.0869],'FontSize',12,'Interpreter','Latex')
axis([0 1.2 1e-3 1e0])
ax=gca;
ax.LineWidth=1.2;
ax.FontSize=12;