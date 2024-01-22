function simplexm
% viz. http://en.wikipedia.org/wiki/Nelder%E2%80%93Mead_method

function f=f(x1,x2)
	f=100*(x1-x2^2)^2+(1-x1)^2;
	% f=x1^2+x2^2;
end

alpha = 1; % koeficient zmeny velikosti pri reflexi
gamma = 2; % koeficient zvetseni
rho = 0.5; % koeficient zmenseni

c = zeros(2,1);

% 3 pocatecni body (ve 2D prostoru)
x = [0.1 -15.2; 4.7 19; 14.8 5.9];

% hodnoty v pocatecnich bodech
y(1)=f(x(1,1),x(1,2));
y(2)=f(x(2,1),x(2,2));
y(3)=f(x(3,1),x(3,2));

for k=1:30
	% body chceme mit serazene y(1)<y(2)<y(3)
	if y(3) < y(2) % prohozeni 2 a 3
		[x(2,1), x(3,1)] = deal(x(3,1), x(2,1));
		[x(2,2), x(3,2)] = deal(x(3,2), x(2,2));
		[y(2), y(3)] = deal(y(3), y(2));
        
        delete(findall(gcf,'type','annotation')); 
        [x(4,1), x(4,2)] = deal(x(1,1), x(1,2));
        plot(x(1,1),x(1,2),'ro',x(2,1),x(2,2),'bo',x(3,1),x(3,2),'go',...
        x(:,1),x(:,2),'k','MarkerSize',12);
        title('Prohozeni bodu 2 a 3');
        legend('bod 1', 'bod 2', 'bod 3', 'Location', 'northeastoutside');
        annotation('textbox',[.85 .6 .95 .2],'String','y(3) < y(2) => prohozeni','EdgeColor','none');
        waitforbuttonpress
	end
	if y(2) < y(1) % prohozeni 1 a 2
		[x(1,1), x(2,1)] = deal(x(2,1), x(1,1));
		[x(1,2), x(2,2)] = deal(x(2,2), x(1,2));
		[y(1), y(2)] = deal(y(2), y(1));
        
        delete(findall(gcf,'type','annotation')); 
        [x(4,1), x(4,2)] = deal(x(1,1), x(1,2));
        plot(x(1,1),x(1,2),'ro',x(2,1),x(2,2),'bo',x(3,1),x(3,2),'go',...
        x(:,1),x(:,2),'k','MarkerSize',12);
        title('Prohozeni bodu 1 a 2');
        legend('bod 1', 'bod 2', 'bod 3', 'Location', 'northeastoutside');
        annotation('textbox',[.85 .6 .95 .2],'String','y(2) < y(1) => prohozeni','EdgeColor','none');
        waitforbuttonpress
		if y(3) < y(2) % prohozeni 2 a 3
			[x(2,1), x(3,1)] = deal(x(3,1), x(2,1));
			[x(2,2), x(3,2)] = deal(x(3,2), x(2,2));
			[y(2), y(3)] = deal(y(3), y(2));
            
            delete(findall(gcf,'type','annotation')); 
            [x(4,1), x(4,2)] = deal(x(1,1), x(1,2));
            plot(x(1,1),x(1,2),'ro',x(2,1),x(2,2),'bo',x(3,1),x(3,2),'go',...
            x(:,1),x(:,2),'k','MarkerSize',12);
            title('Prohozeni bodu 2 a 3');
            legend('bod 1', 'bod 2', 'bod 3', 'Location', 'northeastoutside');
            annotation('textbox',[.85 .6 .95 .2],'String','y(3) < y(2) => prohozeni','EdgeColor','none');
            waitforbuttonpress
		end
	end
	
	% vypis hodnot
	x
	y

	% vypocet x0 (c(i)) v tezisti vsech bodu krome posledniho
	for i=1:2
		c(i) = 0;
		for j=1:2
			c(i) = c(i) + x(j,i)/2;
		end
    end
    
    delete(findall(gcf,'type','annotation')) ;
	[x(4,1), x(4,2)] = deal(x(1,1), x(1,2));
    plot(x(1,1),x(1,2),'ro',x(2,1),x(2,2),'bo',x(3,1),x(3,2),'go', ...
    c(1),c(2),'mo',x(:,1),x(:,2),'k','MarkerSize',12);
    title('Vypocet teziste');
    legend('bod 1','bod 2','bod 3','teziste','Location','northeastoutside');
    waitforbuttonpress
    
	% reflexe (oproti tezisti)
	for i=1:2
		xt(i) = c(i) + alpha*( c(i)-x(3,i) );
	end
	yt = f(xt(1), xt(2));
	
    plot(x(1,1),x(1,2),'ro',x(2,1),x(2,2),'bo',x(3,1),x(3,2),'go', ...
    c(1),c(2),'mo',xt(1), xt(2), 'yo', x(:,1),x(:,2),'k','MarkerSize',12);
	title('Reflexe vuci tezisti');
    legend('bod 1','bod 2','bod 3','teziste', 'xt', 'Location','northeastoutside');
    waitforbuttonpress
    
	if yt<y(3) % pokud je ozrcadleny bod nizsi, nez nas nejvyssi
		for i=1:2 % nahradime posledni novym
			x(3,i) = xt(i);
		end
		y(3) = yt; 
        
        delete(findall(gcf,'type','annotation')) 
        plot(x(1,1),x(1,2),'ro',x(2,1),x(2,2),'bo',x(3,1),x(3,2),'go', ...
        c(1),c(2),'mo',x(:,1),x(:,2),'k','MarkerSize',12);
        title('Prohozeni posledniho s novym');
        legend('bod 1','bod 2','bod 3','teziste', 'Location','northeastoutside');
        annotation('textbox',[.85 .6 .95 .2],'String','yt < y(3) => nahrazeni','EdgeColor','none');
        waitforbuttonpress
		if yt<y(1) % pokud je nizsi, nez nas nejnizsi
			for i=1:2 % provedeme reflexi se zvetsenim (oproti tezisti) s koeficientem gamma
				xe(i) = c(i) + gamma*( xt(i)-c(i) );
			end
			ye = f(xe(1), xe(2));
            y(3) = yt; 
            
            delete(findall(gcf,'type','annotation')) 
            plot(x(1,1),x(1,2),'ro',x(2,1),x(2,2),'bo',x(3,1),x(3,2),'go', ...
            c(1),c(2),'mo',xe(1), xe(2), 'co', x(:,1),x(:,2),'k','MarkerSize',12);
            title('Reflexe vuci tezisti se zvetsenim');
            legend('bod 1','bod 2','bod 3','teziste', 'xe', 'Location','northeastoutside');
            annotation('textbox',[.85 .6 .95 .2],'String','yt < y(1) => reflexe','EdgeColor','none');
            waitforbuttonpress
			if ye<yt  % pokud je vysledek lepsi, nez samotna reflexe
				for i=1:2 % nahradime posledni bod novym
					x(3,i) = xe(i);
				end
				y(3) = ye;
                
                delete(findall(gcf,'type','annotation')) 
                plot(x(1,1),x(1,2),'ro',x(2,1),x(2,2),'bo',x(3,1),x(3,2),'go', ...
                c(1),c(2),'mo', x(:,1),x(:,2),'k','MarkerSize',12);
                title('Nahrazeni posledniho novym');
                legend('bod 1','bod 2','bod 3','teziste', 'Location','northeastoutside');
                annotation('textbox',[.85 .6 .95 .2],'String','ye < yt =>, vysledek lepsi nez reflexe','EdgeColor','none');
                waitforbuttonpress
			end
		end
	end
	
	if yt>y(2) % pokud je ozrcadleny bod vetsi, nez nas prostredni
		for i=1:2 % provedeme zmenseni (oproti tezisti) s koeficientem rho
			xc(i) = c(i)+rho*( x(3,i)-c(i) );
		end
		yc = f(xc(1),xc(2));
        
        delete(findall(gcf,'type','annotation')) 
        plot(x(1,1),x(1,2),'ro',x(2,1),x(2,2),'bo',x(3,1),x(3,2),'go', ...
        c(1),c(2),'mo', xc(1), xc(2), 'co', x(:,1),x(:,2),'k','MarkerSize',12);
        title('Zmenseni oproti tezisti');
        legend('bod 1','bod 2','bod 3','teziste','xc', 'Location','northeastoutside');
        annotation('textbox',[.85 .6 .95 .2],'String','yt > y(2) => zmenseni','EdgeColor','none');
        waitforbuttonpress
		if yc<y(3) % pokud je novy bod nizsi, nez nas nejvyssi
			for i=1:2 % vymenime je
				x(3,i) = xc(i);
			end
			y(3) = yc;
            
            delete(findall(gcf,'type','annotation')) 
            plot(x(1,1),x(1,2),'ro',x(2,1),x(2,2),'bo',x(3,1),x(3,2),'go', ...
            c(1),c(2),'mo', x(:,1),x(:,2),'k','MarkerSize',12);
            title('Prohozeni bodu 3 a xc');
            legend('bod 1','bod 2','bod 3','teziste', 'Location','northeastoutside');
            annotation('textbox',[.85 .6 .95 .2],'String','yc < y(3) => prohozeni','EdgeColor','none');
            waitforbuttonpress
		else % v opacnem pripade provedeme zmenseni ve vsech smerech (2,3) k minimu (1)
			for i=2:3 % zmensujeme smery 2 a 3, na minimum nesahame
				for j=1:2 % zmenseni (v puvodnich smerech) s koeficientem rho
					x(i,j) = x(1,j) + rho*( x(i,j)-x(1,j) );
				end
				y(i) = f( x(i,1), x(i,2) );
                
                delete(findall(gcf,'type','annotation')) 
                plot(x(1,1),x(1,2),'ro',x(2,1),x(2,2),'bo',x(3,1),x(3,2),'go', ...
                c(1),c(2),'mo', x(:,1),x(:,2),'k','MarkerSize',12);
                title('Zmenseni smerem k minimu ve vsech smerech');
                legend('bod 1','bod 2','bod 3','teziste', 'Location','northeastoutside');
                waitforbuttonpress
			end
		end
	end
end
end
