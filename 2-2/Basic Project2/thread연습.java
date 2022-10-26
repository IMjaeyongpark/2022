class Calculator {
	private int memory;

	public int getMemory() {
		return memory;
	}

	public synchronized void setMemory(int memory) {
		this.memory = memory;
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		System.out.println(Thread.currentThread().getName() + " " + this.getMemory());
	}
}

class User1 extends Thread {

	Calculator cal;

	public void setCal(Calculator cal) {
		this.cal = cal;
	}

	@Override
	public void run() {
		cal.setMemory(100);

	}
}

class User2 extends Thread {

	Calculator cal;

	public void setCal(Calculator cal) {
		this.cal = cal;
	}

	@Override
	public void run() {
		cal.setMemory(50);

	}
}

public class Main {
	public static void main(String[] ags) {
		Calculator cal = new Calculator();
		User1 u1 = new User1();
		u1.setCal(cal);
		u1.start();

		User2 u2 = new User2();
		u2.setCal(cal);
		u2.start();
	}
}
