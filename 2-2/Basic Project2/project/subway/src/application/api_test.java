package application;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;

//도착정보 가져오기
public class api_test {
	static String test(String name) throws IOException, ParseException {
		String key = "754f4a48736a616537364b6f785952";

		StringBuilder urlBuilder = new StringBuilder("http://swopenapi.seoul.go.kr/api/subway");

		urlBuilder.append("/" + URLEncoder.encode(key, "UTF-8"));
		urlBuilder.append("/" + URLEncoder.encode("json", "UTF-8"));
		urlBuilder.append("/" + URLEncoder.encode("realtimeStationArrival", "UTF-8"));

		urlBuilder.append("/" + URLEncoder.encode("0", "UTF-8"));
		urlBuilder.append("/" + URLEncoder.encode("5", "UTF-8"));

		urlBuilder.append("/" + URLEncoder.encode(name, "UTF-8"));
		URL url = new URL(urlBuilder.toString());
		HttpURLConnection conn = (HttpURLConnection) url.openConnection();
		conn.setRequestMethod("GET");
		conn.setRequestProperty("Content-type", "application/xml");
		System.out.println("Response code: " + conn.getResponseCode());
		BufferedReader rd;
		// 서비스코드가 정상이면 200~300사이의 숫자가 나옵니다.
		if (conn.getResponseCode() >= 200 && conn.getResponseCode() <= 300) {
			rd = new BufferedReader(new InputStreamReader(conn.getInputStream()));
		} else {
			rd = new BufferedReader(new InputStreamReader(conn.getErrorStream()));
		}
		StringBuilder sb = new StringBuilder();
		String line;
		while ((line = rd.readLine()) != null) {
			sb.append(line);
		}
		JSONParser parser = new JSONParser();
		// 2. 문자열을 JSON 형태로 JSONObject 객체에 저장.
		JSONObject obj = (JSONObject) parser.parse(sb.toString());
		// 3. 필요한 리스트 데이터 부분만 가져와 JSONArray로 저장.
		JSONArray dataArr = (JSONArray) obj.get("realtimeArrivalList");

		JSONObject da = (JSONObject) dataArr.get(0);
		//도착 정보 추출
		String da1 = (String) da.get("arvlMsg2");
		da1 = da1.replace("[", "");
		da1 = da1.replace("]", "");
		rd.close();
		conn.disconnect();

		return da1;
	}
}
