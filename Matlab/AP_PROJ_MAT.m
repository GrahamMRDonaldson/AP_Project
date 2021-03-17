device = serialport("COM3",115200);
samples = 512;
data = [];
index = 1;
sampling_freq = 10500;
%3.78
%{
274.7115
308.343
346.1115
366.6915
411.6
462
518.574
549.4125

248.5485
278.977
313.1485
331.7685
372.4
418
469.186
497.0875
%}


while 1
    for i = 1:samples
        data(i) = str2num(readline(device));
    end
    
    data = data * 5 / 1023;
    data = data - 3.78;
    
    
    Y = fft(data); % calculate fft
    P2 = abs(Y/samples);
    P1 = P2(1:samples/2+1);
    P1(2:end-1) = 2*P1(2:end-1);
    f = sampling_freq*(0:(samples/2))/samples;
    P1(1) = 0;
    [pks,locs] = findpeaks(P1,f, 'MinPeakHeight',0.1);
    
    figure(1);
    plot(data); 
    
    figure(2);
    plot(f, P1); 
    ylim([0 1]); xlim([0 1600]);
    text(locs+.02,pks,num2str((1:numel(pks))'));
    
    if(~isempty(locs))
        freq = locs(1);
        if(freq < 274.7115 && freq > 248.5485)
            write(device,1,"uint8");
        end
        if(freq < 308.343 && freq > 278.977)
            write(device,2,"uint8");
        end
        if(freq < 346.1115 && freq > 313.1485)
            write(device,3,"uint8");
        end
        if(freq < 366.6915 && freq > 331.7685)
            write(device,4,"uint8");
        end
        if(freq < 411.6 && freq > 372.4)
            write(device,5,"uint8");
        end
        if(freq < 462 && freq > 418)
            write(device,6,"uint8");
        end
        if(freq < 518.574 && freq > 469.186)
            write(device,7,"uint8");
        end
        if(freq < 549.4125 && freq > 497.0875)
            write(device,8,"uint8");
        end
    else
        write(device,0,"uint8");
    end
    
    
    
    
end

