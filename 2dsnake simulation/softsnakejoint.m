function [xdot]=softsnakejoint(t,x,C1,C2,D,Z,e,H,JI,m,g,l,Ct,Cn,Ut,Un,w,ta,N,a,b,c,phio,Fsection)

% global PHI;
% kh=0.1;
% dtheta=-0.3;
% phio=kh*(dtheta-(5*x(5)+4*x(4)+3*x(3)+2*x(2)+x(1))/5);
% % phio=-0.2;
% phio=0;
% phio1=0;


phi=zeros(N-1);
for i=1:N-1
    phi(i)=sin(w*t+i*ta)+phio;
%     dphi(i)=alfa*w*cos(w*t+(N+1-i)*ta);   
end
%  PHI(c,:)=phi;
% P=[ ];
% kp=70;
% kd=20;
% for i=1:N-1
% P(i)=kp*(phi(i)-x(i))-kd*x(N+2+i);
% end
P=zeros(1,N-1);
for i=1:N-1
P(i)=sign(phi(i));
end
% if t==tspan(c)

% end
% for i=1:N-1
%     if abs(x(i))<0.01
%       if x(i)>0
%           x(i)=0.01;
%       else
%           x(i)=-0.01;
%       end
%     
%     end
% end
theta=zeros(N,1);
for i=1:N
    theta(i)=sum(x(i:N));
end
K=x(1:N-1);
DK=x((N+3):(2*N+1));

Dtheta=zeros(N,1);
for i=1:N
    Dtheta(i)=sum(x((N+2+i):(2*N+2)));
end
DK2=[DK;Dtheta(N)];
% Dtheta=Dtheta';
Sintheta=diag(sin(theta));
Costheta=diag(cos(theta));
T=zeros(N-1,1);
ST1=zeros(N,N);
CT1=ST1;
ST2=ST1;
CT2=ST1;
STF1=zeros(N,N);
STF2=STF1;
CTF1=STF1;
CTF2=STF1;
L=zeros(N-1,1);
for i=1:N-1
    L(i)=2*abs(l/K(i)*sin(K(i)/2));
end
for i=1:N-1
    T(i)=(theta(i)+theta(i+1))/2;
end
for i=1:N
    if i==1
        ST1(i,:)=0;
    else
    ST1(i,i)=L(i-1)*sin(T(i-1));
    end
end
for i=1:N
    if i==1
        CT1(i,:)=0;
    else
    CT1(i,i)=L(i-1)*cos(T(i-1));
    end
end
for i=1:N
    if i==N
        ST2(i,:)=0;
    else
    ST2(i,i)=L(i)*sin(T(i));
    end
end
for i=1:N
    if i==N
        CT2(i,:)=0;
    else
    CT2(i,i)=L(i)*cos(T(i));
    end
end
for i=1:N
    if i==1
        STF1(i,:)=0;
    else
    STF1(i,i-1)=L(i-1)*sin(T(i-1));
    end
end
for i=1:N
    if i==1
        CTF1(i,:)=0;
    else
    CTF1(i,i-1)=L(i-1)*cos(T(i-1));
    end
end
for i=1:N
    if i==N
        STF2(i,:)=0;
    else
    STF2(i,i)=L(i)*sin(T(i));
    end
end
for i=1:N
    if i==N
        CTF2(i,:)=0;
    else
    CTF2(i,i)=L(i)*cos(T(i));
    end
end

B1=zeros(N-1,N);
B2=zeros(N-1,N);
B3=zeros(N-1,N);
B4=zeros(N-1,N);
B7=zeros(N-1,N);
B5=zeros(N-1,N-1);
B6=zeros(N-1,N-1);
B8=zeros(N-1,N-1);
B9=zeros(N-1,N-1);
    
for i=1:N-1
    B1(i,i)=cos(theta(i))/K(i);
    B1(i,i+1)=-cos(theta(i+1))/K(i);
end
for i=1:N-1
    B2(i,i)=-DK(i)/K(i)^2;
    B2(i,i+1)=DK(i)/K(i)^2;
end
for i=1:N-1
    B3(i,i)=-sin(theta(i))/K(i);
    B3(i,i+1)=sin(theta(i+1))/K(i);
end
for i=1:N-1
    B4(i,i)=-2*DK(i)*cos(theta(i))/K(i)^2;
    B4(i,i+1)=2*DK(i)*cos(theta(i+1))/K(i)^2;
end
for i=1:N-1
    B5(i,i)=(sin(theta(i+1))-sin(theta(i)))/K(i)^2;
end
for i=1:N-1
    B6(i,i)=2*(sin(theta(i))-sin(theta(i+1)))/K(i)^3;
end
for i=1:N-1
    B7(i,i)=2*DK(i)*sin(theta(i))/K(i)^2;
    B7(i,i+1)=-2*DK(i)*sin(theta(i+1))/K(i)^2;
end
for i=1:N-1
    B8(i,i)=(cos(theta(i+1))-cos(theta(i)))/K(i)^2;
end
for i=1:N-1
    B9(i,i)=2*(cos(theta(i))-cos(theta(i+1)))/K(i)^3;
end
STT1=ST2*C2-ST1*C1;
CTT1=CT2*C2-CT1*C1;
Dx=l*Z*((diag(diag(Dtheta(1:N-1))*(cos(theta(1:N-1)))-diag(Dtheta(2:N))*(cos(theta(2:N))))*K-diag(sin(theta(1:N-1))-sin(theta(2:N)))*DK)./(K.^2))+e*x(2*N+3);
Dy=l*Z*((diag(diag(Dtheta(1:N-1))*(sin(theta(1:N-1)))-diag(Dtheta(2:N))*(sin(theta(2:N))))*K-diag(cos(theta(2:N))-cos(theta(1:N-1)))*DK)./(K.^2))+e*x(2*N+4);
% MT=JI+m*l*STT1*((D*D')\B1)+m*l*CTT1*((D*D')\B3);
% WT=m*l*STT1*((D*D')\B3)-m*l*CTT1*((D*D')\B1);
% GT=m*l*STT1*((D*D')\B4)+m*l*CTT1*((D*D')\B7);
% MK=m*l*STT1*((D*D')\B5)+m*l*CTT1*((D*D')\B8);
% WK=m*l*STT1*((D*D')\B6)+m*l*CTT1*((D*D')\B9);
MT=JI+m*l*STT1/(D*D')*B1+m*l*CTT1/(D*D')*B3;
WT=m*l*STT1/(D*D')*B3-m*l*CTT1/(D*D')*B1;
GT=m*l*STT1/(D*D')*B4+m*l*CTT1/(D*D')*B7;
MK=m*l*STT1/(D*D')*B5+m*l*CTT1/(D*D')*B8;
WK=m*l*STT1/(D*D')*B6+m*l*CTT1/(D*D')*B9;
MK=[MK zeros(N,1)];
WK=[WK zeros(N,1)];
% OF1=H'*(-STT1*inv(D*D')*D-(STF2-STF1));
% OF2=H'*(CTT1*inv(D*D')*D+(CTF2-CTF1));
% OF1=H'*(-STT1*((D*D')\D)-(STF2-STF1));
% OF2=H'*(CTT1*((D*D')\D)+(CTF2-CTF1));
OF1=H'*(-STT1/(D*D')*D-(STF2-STF1));
OF2=H'*(CTT1/(D*D')*D+(CTF2-CTF1));
M=H'*MT*H+H'*MK;
W=H'*WT*diag(H*DK2)*H*DK2+H'*WK*diag(DK2)*DK2;
G=H'*GT*(H*DK2);
M21=[M(N,1:N-1);zeros(1,N-1);zeros(1,N-1)];
M22=[M(N,N) 0 0;0 N*m 0;0 0 N*m];
W2=[W(N);0;0];
G2=[G(N);0;0];
F=[OF1(N,:) OF2(N,:);-ones(1,N) zeros(1,N);zeros(1,N) -ones(1,N)];
%FR=-[Ct*(Costheta)^2+Cn*(Sintheta)^2 (Ct-Cn)*Sintheta*Costheta;(Ct-Cn)*Sintheta*Costheta Ct*(Sintheta)^2+Cn*(Costheta)^2]*[Dx;Dy];
FR=-m*g*[Ut*Costheta -Un*Sintheta;Ut*Sintheta Un*Costheta]*atan(100*[Costheta Sintheta; -Sintheta Costheta]*[Dx;Dy])/pi;
%FR=-m*g*[Ut*Costheta -Un*Sintheta;Ut*Sintheta Un*Costheta]*sign([Costheta Sintheta; -Sintheta Costheta]*[Dx;Dy]);

xdot=zeros(2*N+4,1);
xdot(1:(N+2))=x((N+3):(2*N+4));
% xdot((N+3):(2*N+1))=P';
% xdot((2*N+2):(2*N+4))=-inv(M22)*(W2+F*FR)-inv(M22)*M21*P';
xdot((N+3):(2*N+1))=-a*x(N+3:2*N+1)-b*(x(1:N-1))+c*P';
% xdot((2*N+2):(2*N+4))=-inv(M22)*(W2+G2+F*FR)-inv(M22)*M21*(a1*x(N+3:2*N+1)+a2*(x(1:N-1))+alfa*P');
xdot((2*N+2):(2*N+4))=-inv(M22)*(W2+G2+F*FR)-(M22)\M21*(Fsection*L.*P');
end
