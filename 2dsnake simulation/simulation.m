
clear;
close all;
clc;
N=5;
l=0.05;
m=0.04;%Mass of each link
g=9.8;%Gravity acceleration 
J=0.0009;%Moment of inertia of each link
Ct=0.1;%Friction factor on tangential direction
Cn=1;%Friction factor on normal direction
Ut=0.04;
Un=0.5;
% Ut=0.001;
% Un=1;
DS=0.035*0.0071/2;
DL=1;
ta=2*pi/N;%Locomotion delay
phio=0; %Locomotion phase offset
% 6
% C0=0.8177;
% tau1=0.2164;
% tau2=0.2164;
Fsection=41368.5438*DS;
% 7
% C0=1.376;
% tau1=0.2164;
% tau2=0.2164;
% 8
%Coefficient of actuator dynamic
C0=1.8469;
tau1=0.2281;
tau2=0.2281;
a=1/tau1+1/tau2;
b=1/tau1/tau2;
c=C0/tau1/tau2;
w=3*pi;%Locomotion frequency
xphi=[];
yphi=[];
tanphi=[];
Ntanphi=[];
D=zeros(N-1,N);
e=ones(N,1);

for i=1:N-1
    D(i,i)=1;
    D(i,i+1)=-1;
end
C1=zeros(N,N-1);
C2=zeros(N,N-1);
for i=1:N
    if i==1
    elseif i==2
        C1(i,i-1)=1;
    else
    C1(i,i-2)=-1;
    C1(i,i-1)=1;
    end
end
for i=1:N
    if i==N
    elseif i==N-1
    C2(i,N-1)=-1;
    else
    C2(i,i)=-1;
    C2(i,i+1)=1;
    end
end
H=triu(ones(N,N),0);
JI=diag(2*J/ones(N,1));
Z=D'/(D*D');

totalTime=100;
tspan=0:0.1:totalTime;
xx=zeros(1,N);
for i=1:N
   xx(i)=0;
end
for i=1:N
if abs(xx(i))<0.01
         if xx(i) > 0
            xx(i)=0.01;
         else
            xx(i)=-0.01;
         end
end
end
dxx=zeros(1,N);
x0=[xx 0 0 dxx 0 0];
tic;

[t,x]=ode45(@softsnakejoint,tspan,x0,[],C1,C2,D,Z,e,H,JI,m,g,l,Ct,Cn,Ut,Un,w,ta,N,a,b,c,phio,Fsection);
T=toc;


%
dxp=zeros((totalTime)/0.1+1,N-1);
dyp=dxp;
xp=zeros((totalTime)/0.1+1,N);
yp=xp;
figure
set(gca,'fontsize',18);
for i=1:1:(totalTime)/0.1
for j=1:N-1
       
        dxp(i,j)=(sin(sum(x(i,j:N)))-sin(sum(x(i,j+1:N))))/x(i,j);
        dyp(i,j)=(cos(sum(x(i,j:N)))-cos(sum(x(i,j+1:N))))/x(i,j);
end
    xp(i,:)=l*Z*dxp(i,1:N-1)'+x(i,N+1)*ones(N,1);
    yp(i,:)=-l*Z*dyp(i,1:N-1)'+x(i,N+2)*ones(N,1);

curvatureplot(xp(i,:),yp(i,:),-1./x(i,1:N-1)*l,N,1);
axis([min(xp(i,:))-0.5 max(xp(i,:))+0.5 min(yp(i,:))-0.5 min(yp(i,:))+0.5])
axis equal
drawnow
pause(0.1);
hold off

end



