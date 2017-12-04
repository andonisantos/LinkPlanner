%%MQAM system
clc
clear all
close all
%% Theoretical curve
figure
n0=(1e-3)*(1e-6); 
% xdBm=linspace(-120,-50,1000);
% x=(10.^(xdBm./10))/1000;
% func=erfc(sqrt(x/(2*n0)));
% 
% plot(x,func)
% grid on
EbNodBm=linspace(-160,-20,200);
EbNo=(1e-3)*(10.^(EbNodBm/10)); 
%k=2;
%M=2^k;
%x=sqrt(3*k*EbNo/(M-1));
Pb=0.5*erfc(sqrt(2*EbNo/n0));
%Pb=(4/k)*(1-(1/sqrt(M)))*(1/2)*erfc(x/sqrt(2*n0));
plot(EbNodBm,Pb,'LineWidth',2)
grid on
axis([-140 -20 0 0.6])
xlabel('Optical power (dBm)')
ylabel('BER')
legend('QPSK theoritical curve')
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