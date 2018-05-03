                                                                                                                                                                                                                                                                                                                                                                                              
function []=curvatureplot(xp,yp,r,N,tag)
flag=[];
a=[];
b=[];
c=[];
d=[];
e=[];
xn=[];
yn=[];
for i=1:N-1
    if r(i)<=0
       r(i)=abs(r(i));
       flag(i)=1;
    else
        flag(i)=0;
    end
end
   
d = ((xp(2:N)-xp(1:N-1)).^2+(yp(2:N)-yp(1:N-1)).^2).^(1/2); % Distance between points
% a = atan2(xp(2:11)-xp(1:10),-(yp(2:11)-yp(1:10)));
a = atan2(yp(2:N)-yp(1:N-1),(xp(2:N)-xp(1:N-1)))+pi/2;
b = asin(d/2./r); % Half arc angle
for i=1:N-1
c(i,:) = linspace(a(i)-b(i),a(i)+b(i)); % Arc angle range
end
e = sqrt(r.^2-d.^2/4); % Distance, center to midpoint
for i=1:N-1
if flag(i)==1
xn(:,i) = (xp(i)+xp(i+1))/2-e(i)*cos(a(i))+r(i)*cos(c(i,:)); % Cartesian coords. of arc
yn(:,i) = (yp(i)+yp(i+1))/2-e(i)*sin(a(i))+r(i)*sin(c(i,:));
else
xn(:,i) = (xp(i)+xp(i+1))/2+e(i)*cos(a(i))-r(i)*cos(c(i,:)); % Cartesian coords. of arc
yn(:,i) = (yp(i)+yp(i+1))/2+e(i)*sin(a(i))-r(i)*sin(c(i,:));
end
end



% plot(xn,yn,'b',xp,yp,'o')
if tag==0
plot(xn,yn,'b');
else
plot(xn,yn,'r');
end

% axis([mean(xp)-0.1 mean(xp)+0.1 mean(yp)-0.1 mean(yp)+0.1])
% axis([-0.1 0.8 -0.02 0.02])