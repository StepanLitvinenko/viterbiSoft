

fid = fopen('codedData.dat','wb');
f2id = fopen('data.dat','wb');


trellis = poly2trellis(3,[5 7]);
data = [0 1 1 0 0 1 1 1 0 0 1 1 1 0 1 0 1 0 0];




codedData = convenc(data,trellis);



len = length(codedData);

noise = wgn(1,len,0.001);
codedData = codedData*2 - 1;
codDatNoise = addAWGN(codedData, 2);
codedDatNoise = codedData+noise;

% savedData = data(1:end-2);

fwrite(fid, codDatNoise, 'float32');
fwrite(f2id, data, 'float32'); 

fclose(fid); 
fclose(f2id);