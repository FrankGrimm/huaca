package org.fg.huaca.devices;

import java.util.ArrayList;
import java.util.List;

import org.apache.log4j.Logger;

import jssc.SerialPort;
import jssc.SerialPortList;

public class DeviceDiscovery {
	private final Logger log = Logger.getLogger(DeviceDiscovery.class.getName());
	
	private DeviceDiscovery() {
	
	}

	private static DeviceDiscovery _instance = null;
	public static DeviceDiscovery getInstance() {
		if (_instance == null)
			_instance = new DeviceDiscovery();
		
		return _instance;
	}
	
	public List<String> getPortNames() {
		String[] portNames = SerialPortList.getPortNames();
		List<String> result = new ArrayList<>();
		
		for (String portName: portNames) {
			if (portBlacklist.contains(portName))
				continue;
			result.add(portName);
		}
		
        return result;
	}
	

	private List<String> portBlacklist = new ArrayList<>();
	private List<Device> registeredDevices = new ArrayList<>();
	
	public List<String> getPortBlacklist() {
		return portBlacklist;
	}

	public void setPortBlacklist(List<String> portBlacklist) {
		this.portBlacklist = portBlacklist;
	}
	
	public void blacklistPortname(String portName) {
		if (this.portBlacklist.contains(portName))
			return;
		this.portBlacklist.add(portName);
	}

	public List<Device> getRegisteredDevices() {
		return registeredDevices;
	}
	
	public void registerDevice(Device dev) {
		registeredDevices.add(dev);
		log.info("Registered device: " + dev.toString());
	}

	public void scan(int maxBuffer, int timeout) {
		this.scan(maxBuffer, timeout, SerialPort.BAUDRATE_19200, SerialPort.DATABITS_8, 
				SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
	}
	
	public void scan(int maxBuffer, int timeout, int baudRate, int dataBits, int stopBits, int parity) {
		
		for (String currentPortname: getPortNames()) {
			SyncInitializer si = new SyncInitializer(currentPortname, maxBuffer, timeout, baudRate, dataBits, stopBits, parity);
			String deviceInitializer = null; 
			try {
				deviceInitializer = si.tryGetInitializer();
			} catch (Exception e) {
				log.warn("Failed to get initializer string on port " + currentPortname + ": " + e.getMessage(), e);
				continue;
			}
			if (deviceInitializer == null) {
				log.info("No initializer string found on port " + currentPortname);
				continue;
			}
			
			log.debug(currentPortname + " Device Initializer: <" + deviceInitializer + ">");
			
			for (Device currentDevice: registeredDevices) {
				if (currentDevice.getHandshakeID().equals(deviceInitializer)) {
					if (currentDevice.isDiscovered()) {
						log.warn("Device " + currentDevice.toString() + " matches, but was already discovered.");
						continue;
					}
					
					log.info("Device discovered: " + currentDevice + " on port " + currentPortname);
					currentDevice.setPortName(currentPortname);
				}
			}
		}
	}

}
