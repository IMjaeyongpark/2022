import org.jsoup.Connection;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import java.io.IOException;

public class test {
	public static void main(String[] args) {
		String URL = "https://github.com/IMjaeyongpark/2022/blob/main/2-1/Basic%20Project1/project/19-20.txt";
		try {
			Document document= Jsoup.connect(URL).get();
            Elements imageUrlElements = document.getElementsByClass("Box-body p-0 blob-wrapper data type-text  gist-border-0");
            
            Elements titleElements = document.select("td");
            for (int j = 0; j < titleElements.size(); j++) {
                final String title = titleElements.get(j).text();
                System.out.println(title);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
	}
}
