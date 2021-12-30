<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<!-- maria db connection dependency -->
<%@ page import="java.sql.DriverManager" %>
<%@ page import="java.sql.Connection" %>
<%@ page import="java.sql.PreparedStatement" %>

<%@ page import="java.util.Date" %>
<%@ page import="java.text.SimpleDateFormat" %>
<%
	Date nowTime = new Date();
	SimpleDateFormat sf = new SimpleDateFormat("yyyyMMddhhmmss");
%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>결제 완료</title>
</head>
<body>
	<h1>결제가 완료되었습니다.</h1>
<%
	// 작성한 값 받아오기
	int number = 1;
	String name = "mask";
	String major = "yaho";
	
	// mariaDB 준비
	Class.forName("org.mariadb.jdbc.Driver");
	System.out.println("mariadb 사용가능");
	
	// mariaDB 연결
	Connection conn = DriverManager.getConnection("jdbc:mariadb://127.0.0.1:3306/mask","root","sulc5246");
	System.out.println(conn + "<-- conn");
	
	// 쿼리
	PreparedStatement stmt = conn.prepareStatement("insert into masktable(id, name, major) values(?,?,?)"); // ?표현식 : 변수자리
	stmt.setInt(1, number);
	stmt.setString(2, name);
	stmt.setString(3, sf.format(nowTime));
    System.out.println(stmt + "<-- stmt");
	
	// 쿼리 실행
	stmt.executeUpdate();
    conn.close(); // DB 종료
%>
</body>
</html>