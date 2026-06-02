% https://es.mathworks.com/help/matlab/import_export/read-streaming-data-from-arduino.html
% Cerramos las conexiones serialport existentes
delete(serialportfind);
% Guardamos los datos del serialport en "serialObj"
serialObj = serialport("COM5",9600);
% Definimos la propiedad Terminator para que coincida con el terminador
% especificado en el codigo de arduino
configureTerminator(serialObj,"CR/LF");
% Vaciamos serialObj para limpiar datos antiguos
flush(serialObj);

% Hacemos un loop para sacar 200 datos    
for i = 1:200
        % Leemos los datos, luego los convertimos de un string a un valor
        % numerico
        data = readline(serialObj);
        numData = str2double(data);
        disp(numData);
end
