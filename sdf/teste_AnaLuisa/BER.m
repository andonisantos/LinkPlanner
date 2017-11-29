%%MQAM system
clc
clear all
%% Theoretical curve
figure
n0=1e-6;
% xdBm=linspace(-120,-50,1000);
% x=(10.^(xdBm./10))/1000;
% func=erfc(sqrt(x/(2*n0)));
% 
% plot(x,func)
% grid on
EbNodB=linspace(-120,-50,100);
EbNo=(10.^(EbNodB/10))/1000;
k=2;
M=2^k;
x=sqrt(3*k*EbNo/(M-1));
Pb=erfc(sqrt(EbNo/n0));
%Pb=(4/k)*(1-(1/sqrt(M)))*(1/2)*erfc(x/sqrt(2*n0));
plot(EbNodB,Pb)
grid on
%% BER parameters: amp=10e3, noise_amp=10e-6, LO_power=0dBm, n_bits=200
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
A=importdata('BER2.txt');
NumLin=size(A,1);
OpticalPower=A(1:NumLin,1);
ber=A(1:NumLin,2);
Up=A(1:NumLin,3);
Lo=A(1:NumLin,4);
yneg=ber-Lo;
ypos=Up-ber;
figure
errorbar(OpticalPower,ber,yneg,ypos,'b*')
grid on
xlabel('Output optical power (dBm)')
ylabel('BER')
hold on
%plot(EbNodB,Pb)
%% BER parameters: amp=10e3, noise_amp=10e-6, LO_power=0dBm, n_bits=4000, buffer_length=512
A=importdata('BER3.txt');
NumLin=size(A,1);
OpticalPower=A(1:NumLin,1);
ber=A(1:NumLin,2);
Up=A(1:NumLin,3);
Lo=A(1:NumLin,4);
yneg=ber-Lo;
ypos=Up-ber;
figure
errorbar(OpticalPower,ber,yneg,ypos,'b*')
grid on
xlabel('Output optical power (dBm)')
ylabel('BER')
hold on