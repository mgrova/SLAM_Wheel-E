load('ticks.txt')

n_ticks_rev=22;

% El tiempo de muestreo es 0.1 y se toman datos cada 10

t=ticks(1:10:end,1)*0.1
r1L=ticks(1:10:end,2)*((2*pi)/n_ticks_rev);
r2L=ticks(1:10:end,3)*((2*pi)/n_ticks_rev);
r3L=ticks(1:10:end,4)*((2*pi)/n_ticks_rev);
r1R=ticks(1:10:end,5)*((2*pi)/n_ticks_rev);
r2R=ticks(1:10:end,6)*((2*pi)/n_ticks_rev);
r3R=ticks(1:10:end,7)*((2*pi)/n_ticks_rev);

figure()
subplot(231);plot(t,r1L);title('ticks/seg r1L');grid;ylim([0 600])
subplot(232);plot(t,r2L);title('ticks/seg r2L');grid;ylim([0 600])
subplot(233);plot(t,r3L);title('ticks/seg r3L');grid;ylim([0 600])

subplot(234);plot(t,r1R);title('ticks/seg r1R');grid;ylim([0 600])
subplot(235);plot(t,r2R);title('ticks/seg r2R');grid;ylim([0 600])
subplot(236);plot(t,r3R);title('ticks/seg r3R');grid;ylim([0 600])

%% Modelo aproximado del motor
Kest=40/25; 
tau=0.8*0.63;
numGs=Kest;
denGs=[tau 1];

Gs=tf(numGs,denGs)

% Disenando un PI para un ts=1s
Ti=0.47
Kp=2.23482*Ti