clc;
clear all;

[data, symbolperiod,sampling,type,number]=readSignal_20171220('S2.sgn');
data_x = data(1:4:end) + 1i.*data(2:4:end);
data_x = real(data_x)' + imag(data_x)'.*1i;
data_y = data(3:4:end) + 1i.*data(4:4:end);
data_y = real(data_y)' + imag(data_y)'.*1i;

real_x = real(data_x(1:end));
imag_x = imag(data_x(1:end));
real_y = real(data_y(1:end));
imag_y = imag(data_y(1:end));


phase_dif = angle(data_x(1:end-1)) - angle(data_y(1:end));


figure (1)

subplot(5,1,1);
plotSignal_20171220(real_x,symbolperiod,sampling,'PhotonStreamXY',number)
subplot(5,1,2);
plotSignal_20171220(imag_x,symbolperiod,sampling,'PhotonStreamXY',number)
subplot(5,1,3);
plotSignal_20171220(real_y,symbolperiod,sampling,'PhotonStreamXY',number)
subplot(5,1,4);
plotSignal_20171220(imag_y,symbolperiod,sampling,'PhotonStreamXY',number)
subplot(5,1,5);
plotSignal_20171220(phase_dif,symbolperiod,sampling,'PhotonStreamXY',number)