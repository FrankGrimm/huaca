package org.fg.huaca;

import org.fg.huaca.devices.DeviceDiscovery;
import org.fg.huaca.devices.impl.HeadController;

public class Runner {

	/**
	 * @param args
	 */
	public static void main(String[] args) {		
		DeviceDiscovery discovery = DeviceDiscovery.getInstance();
		
		for (int blockPortNum = 1; blockPortNum <= 6; blockPortNum++) {
			discovery.blacklistPortname("COM" + Integer.toString(blockPortNum));
		}
		
		discovery.registerDevice(new HeadController());
		discovery.scan(50, 5000);
		
	}

}
