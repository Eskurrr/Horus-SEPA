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
        % Guardamos los datos en "data"
        % Separamos los valores y los guardamos en variables por cada señal que extraemos
        data = readline(serialObj);
        valores = str2double(split(strtrim(data),","));
        if length(valores) == 2
            s1 = valores(1);
            s2 = valores(2);
        end
        disp([s1,s2])
end
