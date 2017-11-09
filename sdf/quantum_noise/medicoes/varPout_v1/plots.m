dataS  = load('Pout_PS.txt');
dataLO = load('Pout_PLO.txt');

nS  = dataS(:,1);
vS  = dataS(:,2);

nLO = dataLO(:,1);
vLO = dataLO(:,2);

% Constantes
sq2 = sqrt(2);
wl = 1.55e-6;
c = 299792458;
h = 6.626070040e-34;
bitPeriod = 1.0e-9;
samplesPerSymbol = 16;
P=c*h/(wl*bitPeriod/samplesPerSymbol);



n1_default = 10;
n2_default = 1e4;
amp = 1e6;

% Cálculo das potências em função do número de fotões
pLO = nLO * P
p2_default = n2_default * P

figure
loglog(nS, vS/(2*P.^2), 'o');
grid
xlabel('Signal photons');
ylabel('Variance');

%%

figure
loglog(nLO, vLO./(2*pLO), 'o');
grid
xlabel('Local Oscillator photons');
ylabel('Variance');
