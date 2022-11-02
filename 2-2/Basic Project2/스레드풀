import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.ThreadPoolExecutor;

public class Main {
	public static void main(String[] ags) throws Exception{
		
		//스레드풀 생성
		ExecutorService executorService = Executors.newFixedThreadPool(2);

		
		for (int i = 0; i < 10; i++) {
			
			//작업 생성
			Runnable runnable = new Runnable() {

				@Override
				public void run() {
					ThreadPoolExecutor threadPoolExecutor = (ThreadPoolExecutor) executorService;

					int poolSize = threadPoolExecutor.getPoolSize();
					String ThreadName = Thread.currentThread().getName();
					System.out.println("[총 스레드 개수: " + poolSize + "] 작업 스레드 이름: " + ThreadName);
					
					int num = Integer.parseInt("as");
				}
				
			};
			
			//작업 처리 요청 (큐에 넣기)
			executorService.execute(runnable);
			
			Thread.sleep(10);
		}
		
		
		executorService.shutdown();
	}
}
