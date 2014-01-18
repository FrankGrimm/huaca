package org.fg.huaca.devices;

import java.nio.charset.Charset;

import jssc.SerialPort;
import jssc.SerialPortException;
import jssc.SerialPortTimeoutException;
import net.sf.json.JSONObject;
import net.sf.json.JSONSerializer;

import org.apache.log4j.Logger;

class SyncInitializer {
	private final Logger log = Logger.getLogger(SyncInitializer.class.getName()); 
	
	private String portName = null;
	private int maxBuffer = 100;
	private int timeout = 1000;
	private int baudRate = 19200;
	private int dataBits = 8;
	private int stopBits = 1;
	private int parity = 0;
	
	public SyncInitializer(String portName, int maxBuffer, int timeout, int baudRate, int dataBits, int stopBits, int parity) {
		this.portName = portName;
		this.maxBuffer = maxBuffer;
		this.timeout = timeout;
		this.baudRate = baudRate;
		this.dataBits = dataBits;
		this.stopBits = stopBits;
		this.parity = parity;
	}
	
	public String tryGetInitializer() throws Exception {
		SerialPort serialPort = new SerialPort(portName);
		byte[] buffer = null;
		
		log.debug(portName + " probing");
		try {
            serialPort.openPort();
            log.debug(portName + " opened");
            serialPort.setParams(baudRate, dataBits, stopBits, parity);
            buffer = serialPort.readBytes(maxBuffer, timeout);
            serialPort.closePort();
            log.debug(portName + " closed");
        } catch (SerialPortTimeoutException ex) {
        	buffer = null;
        	log.warn(portName + " timeout");
		} catch (SerialPortException ex) {
            throw new Exception("Failed to read from serial port " + portName, ex);
        }
		
		if (buffer != null) {
			String bufferContent = new String(buffer, Charset.forName("ASCII"));
			log.trace("Buffer content: <" + bufferContent + ">");
			if (bufferContent.indexOf("{") > -1) {
				bufferContent = bufferContent.substring(bufferContent.indexOf("{"));
			}
			String firstLine = bufferContent.split("\n")[0].trim();
			log.trace("First line in buffer: <" + firstLine + ">");
			if (firstLine.contains("init")) {
				JSONObject obj = (JSONObject)JSONSerializer.toJSON(firstLine);
				if (obj.has("init")) {
					String initID = obj.getString("init");
					if (initID != null)
						return initID;
				}
				
			}
		}

		log.warn(portName + " Failed to retrieve initializer from buffer.");
		return null;
	}
}
