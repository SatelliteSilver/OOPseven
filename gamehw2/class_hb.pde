class hb {
  
    //////////////////
    // constructors //
    //////////////////
    hb() {x = width / 4; y = height /2 ; size = 40;} // constructor 1
    hb(float s) {x = width / 4; y = height / 3; size = s;}  // constructor 2
    hb(float l_x, float l_y, float s) { x = l_x; y = l_y; size = s;} // constructor 3 
  
    ///////////////
    // variables //
    ///////////////
    float x, y, size;
  
    ///////////////
    // functions //
    ///////////////
    // render
    void render() {
        // 캐릭터 몸통
        fill(0, 0, 255); 
        ellipse(x, y, size, size * 1.5);
    
        // 캐릭터 머리
        fill(255, 255, 0);
        ellipse(x, y - size * 0.7, size * 0.8, size * 0.8);
    
        // 캐릭터 눈
        fill(0); 
        ellipse(x - size * 0.2, y - size * 0.7, size * 0.2, size * 0.2);
        ellipse(x + size * 0.2, y - size * 0.7, size * 0.2, size * 0.2);
    }

    // key 입력 받아서 위치 조정 함수
    void move(float dx, float dy) {
        x += dx;
        y += dy;
        
        //화면 밖으로 나가지 않게 하는 기능
        if (x > width - size / 2)
        x = width - size / 2;
        else if (x < size / 2)
        x = size / 2;    
    }
}
