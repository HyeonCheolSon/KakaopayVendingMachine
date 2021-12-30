<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>

<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<script type="text/javascript" src="https://code.jquery.com/jquery-1.12.4.min.js" ></script>
<script type="text/javascript" src="https://cdn.iamport.kr/js/iamport.payment-1.1.5.js"></script>
</head>
<body>
    <script>
    $(function(){
        var IMP = window.IMP; // 생략가능
        IMP.init('imp03027601'); // 'iamport' 대신 부여받은 "가맹점 식별코드"를 사용
        var msg;
        
        IMP.request_pay({
        	pg : 'kcp',
            pay_method : 'card',
            merchant_uid: "order_no_0001", //상점에서 생성한 고유 주문번호
            name : '마스크',
            amount : 1,
            buyer_email : 'iamport@siot.do',
            buyer_name : '구매자이름',
            buyer_tel : '010-1234-5678',
            buyer_addr : '서울특별시 강남구 삼성동',
            buyer_postcode : '123-456',
            m_redirect_url : 'http://3.35.98.45:8080/Kakaopay/insert.jsp'
        }, function(rsp) {
            if ( !rsp.success ) {
            	//결제 시작 페이지로 리디렉션되기 전에 오류가 난 경우
                var msg = '오류로 인하여 결제가 시작되지 못하였습니다.';
                msg += '에러내용 : ' + rsp.error_msg;

                alert(msg);
            }
        });
        
    });
    </script>
 
</body>
</html>
