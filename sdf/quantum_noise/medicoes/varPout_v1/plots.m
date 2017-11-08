dataS  = load('Pout_PS.txt');
dataLO = load('Pout_PLO.txt');

pS  = dataS(:,1);
vS  = dataS(:,2);

pLO = dataLO(:,1);
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

% Normalização da potência

figure
loglog(pS, vS/(2*P), 'o');
grid
xlabel('Signal photons');
ylabel('Variance');

%%

figure
loglog(pLO, vLO./(2*pLO), 'o');
grid
xlabel('Local Oscillator photons');
ylabel('Variance');
