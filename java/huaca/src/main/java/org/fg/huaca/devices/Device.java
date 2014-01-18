package org.fg.huaca.devices;

public abstract class Device {

	private String portName = null;
	private String handshakeID = null;
	
	public String getHandshakeID() {
		return handshakeID;
	}

	protected void setHandshakeID(String handshakeID) {
		this.handshakeID = handshakeID;
	}
	
	public boolean isDiscovered() {
		return this.portName != null;
	}

	public String getPortName() {
		return portName;
	}

	public void setPortName(String portName) {
		this.portName = portName;
	}
	
	private Device() {
	
	}
	
	protected Device(String handshakeID) {
		this();
		this.handshakeID = handshakeID;
	}
	
	@Override
	public String toString() {
		return "[Device #" + this.getClass().getName() + "]";
	}
}
