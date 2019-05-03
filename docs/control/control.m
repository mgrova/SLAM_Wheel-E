tickslog=load('ticks.txt');
pwmlog=load('pwm.log');
n_ticks_rev=22; % Number of slits in the encoders [ticks/s]*(2*pi)[rad]/n_ticks_rev[ticks] = [rad/s]

%% Lets take pwm data (control signal, saturate at [-255,255])
tp=pwmlog(1:end,1);    % Note that the order of data its different from ticks.txt
pwm=pwmlog(1:end,2);

for i=1:length(tp)
   if tp(i)<192
       tp1(i)=tp(i)+4.797;
       pwm1(i)=pwm(i);
   end
end
tp=tp1; clear tp1;
pwm=pwm1; clear pwm1;

pwm=timeseries(pwm,tp);

%figure(); plot(tp,p1l);

%% Encoders data (ticks/s)
% El tiempo de muestreo es 0.1 y se toman datos cada 10
tt=tickslog(1:10:end,1);
r1l=tickslog(1:10:end,2); r2l=tickslog(1:10:end,3); r3l=tickslog(1:10:end,4);
r1r=tickslog(1:10:end,5); r2r=tickslog(1:10:end,6); r3r=tickslog(1:10:end,7);

for i=1:length(r1l)
   if tt(i)<108
       r1l(i)=-r1l(i);
   end
end
ticks=timeseries(r1l,tt);

%figure(); plot(tt, r1L);


%% Lets see pwm and ticks together
 figure(); plot(ticks); grid; hold on; plot(pwm); title('Static cha'); hold off;
 
%%
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