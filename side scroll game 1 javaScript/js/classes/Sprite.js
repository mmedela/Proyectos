class Sprite{
    constructor({position, imgSrc, scale = 1, totalFrames = 1}){
        this.position = position;
        this.width = 50;
        this.height = 150;
        this.img = new Image();
        this.img.src = imgSrc;
        this.scale = scale;
        this.totalFrames = totalFrames;
        this.currentFrame = 0;
        this.framesElapsed = 0;
        this.framesHold = 8;
    }

    draw(canvasContext){
        canvasContext.drawImage(
            this.img,
            this.currentFrame * this.img.width / this.totalFrames,
            0,
            this.img.width/this.totalFrames,
            this.img.height,
            this.position.x,
            this.position.y,
            (this.img.width / this.totalFrames) * this.scale,
            this.img.height * this.scale
        );
    }

    update(canvasContext){
       this.draw(canvasContext);
       this.framesElapsed++;
       if(this.framesElapsed % this.framesHold === 0){
        if(this.currentFrame < this.totalFrames-1) this.currentFrame++;
        else this.currentFrame = 0;
       } 
    }
}

export default Sprite;