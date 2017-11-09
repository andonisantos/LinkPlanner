data = load('power.txt');

n2 = data(:,1);
var_m = data(:,2);

%%
loglog(n2, var_m, '.-')
xlabel('P Local Oscilator (W)')
ylabel('Var[Iout] (A^2)')
grid