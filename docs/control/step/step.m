%% 3 steps in this experiments, from 0 to mid, from mid to high & from 0 to high
tickslog=load('ticks.txt');
pwmlog=load('pwm.log');
data_end = 1500; % Last column data to be read
n_ticks_rev=22; % Number of slits in the encoders [ticks/s]*(2*pi)[rad]/n_ticks_rev[ticks] = [rad/s]
tm=0.1; % Sample time is (at least) 0.1s

%% Lets take pwm data (control signal, saturate at [-255,255])
tp=pwmlog(1:data_end,1);    % Note that the order of data its different from ticks.txt
pwm=pwmlog(1:data_end,2);

tp=tp+2.9;
pwm=timeseries(pwm,tp);

%figure(); plot(tp,p1l);

%% Encoders data (ticks/s)
% El tiempo de muestreo es 0.1 y se toman datos cada 10 (xx)
xx=1;
tt=tickslog(1:xx:data_end,1);
r1l=tickslog(1:xx:data_end,2); r2l=tickslog(1:10:end,3); r3l=tickslog(1:10:end,4);
r1r=tickslog(1:10:end,5); r2r=tickslog(1:10:end,6); r3r=tickslog(1:10:end,7);

ticks=timeseries(r1l,tt);

%figure(); plot(tt, r1L);


%% Lets see pwm and ticks together
 figure(); plot(ticks); grid; hold on; plot(pwm); title('Static cha'); hold off;
 
%% Model: m1l
k1=67/90;
tau1=34.7-33.8;

k2=(93.58-64.36)/(107-90);
tau2=64.78-64.36;

k3=93.13/107;
tau3=127.1-126.8;

m1=tf([k1],[tau1 1]);
m2=tf([k2],[tau2 1]);
m3=tf([k3],[tau3 1]);

sim models.slx
%%
figure(); plot(ticks,'g'); grid; hold on; plot(pwm,'-r'); title('Models'); plot(mod1); plot(mod2); plot(mod3); legend('ticks','pwm','m1','m2','m3'); hold off;

% %% Contiunuos contro
% c=tf([3/0.1],[1 0]);
% c1=c/m1; c2=c/m2; c3=c/m3;
% [c1num,c1den]=tfdata(c1,'v'); [c2num,c2den]=tfdata(c2,'v'); [c3num,c3den]=tfdata(c3,'v');

%% Discrete contol
m1z=c2d(m1,tm,'zoh');
m2z=c2d(m2,tm,'zoh');
m3z=c2d(m3,tm,'zoh');

c=tf([1],[1 -1],tm);

c1=c/m1z;
[c1num,c1den]=tfdata(c1,'v')
c2=c/m2z;
[c2num,c2den]=tfdata(c2,'v')
c3=c/m3z;
[c3num,c3den]=tfdata(c3,'v')

%[z1,p1,nd1]=residue(c1num,c1den);
%[z2,p2,nd2]=residue(c2num,c2den);
%[z3,p3,nd3]=residue(c3num,c3den);
[z1,p1,nd1]=tf2zp(c1num,c1den)
[z2,p2,nd2]=tf2zp(c2num,c2den)
[z3,p3,nd3]=tf2zp(c3num,c3den)



%%
figure()
subplot(231);plot(tt,r1l);title('ticks/seg r1L');grid;ylim([0 600])
subplot(232);plot(tt,r2l);title('ticks/seg r2L');grid;ylim([0 600])
subplot(233);plot(tt,r3l);title('ticks/seg r3L');grid;ylim([0 600])
subplot(234);plot(tt,r1r);title('ticks/seg r1R');grid;ylim([0 600])
subplot(235);plot(tt,r2r);title('ticks/seg r2R');grid;ylim([0 600])
subplot(236);plot(tt,r3r);title('ticks/seg r3R');grid;ylim([0 600])

%% Modelo aproximado del motor
Kest=40/25; 
tau=0.8*0.63;
numGs=Kest;
denGs=[tau 1];

Gs=tf(numGs,denGs)

% Disenando un PI para un ts=1s
Ti=0.47
Kp=2.23482*Ti