import Sprite from "./Sprite.js";

const gravity = 0.7;
class playerSprite extends Sprite{ 
    constructor({position, velocity, color = 'red', imgSrc, scale = 1, totalFrames = 1, 
                offset={x:0, y:0}, framesHold, sprites}){
        super({position, imgSrc, scale, totalFrames, offset, framesHold});
        this.velocity = velocity;
        this.width = 50;
        this.height = 150;
        this.lastKeyPressed;
        this.attacking = false;
        this.attackBox = {
            position:{
                x: this.position.x,
                y: this.position.y
            },
            width: 100,
            height: 50,
            offset
        }
        this.color = color;
        this.health = 100;
        this.currentFrame = 0;
        this.framesElapsed = 0;
        this.sprites = sprites;

        for(const sprite in this.sprites){
            sprites[sprite].img = new Image();
            sprites[sprite].img.src = sprites[sprite].imgSrc;
            console.log(this.sprites);
        }
    }

    update(canvasContext, height){
        this.draw(canvasContext);
        this.trackAnimationFrames();
        this.attackBox.position.y = this.position.y;
        this.attackBox.position.x = this.position.x + this.attackBox.offset.x;

        this.position.y += this.velocity.y;
        this.position.x += this.velocity.x;
        if(this.position.y + this.height + this.velocity.y >= height - 51){
            this.position.y = 375;
            this.velocity.y = 0;
        }else{
            this.velocity.y += gravity;
        }
        console.log(this.position.y);
    }

    canAttack(enemy){
        let a = this.attackBox.position.x + this.attackBox.width >= enemy.position.x;
        let b = this.attackBox.position.x <= enemy.position.x + enemy.width;
        let c = this.attackBox.position.y + this.attackBox.height >= enemy.position.y;
        let d = this.attackBox.position.y <= enemy.position.y + enemy.height;
        return a&&b&&c&&d;
    }

    isAttacking(){
        return this.attacking;
    }

    attack(){
        this.attacking = true;
        setTimeout(()=>{
            this.stopAttack();
        }, 100);
    }
    stopAttack(){
        this.attacking = false;
    }

    isDead(){
        return (this.health <= 0);
    }

    currentHealth(){
        return this.health;
    }

    jump(){
        this.velocity.y = -20;
    }

    stop(){
        this.velocity.x = 0;
    }

    switchAnimationTo (sprite) {
        switch (sprite) {
            case 'idle':
                if(this.img !== this.sprites.idle.img){
                    this.img = this.sprites.idle.img;
                    this.totalFrames = this.sprites.idle.totalFrames;
                    this.currentFrame = 0;
                }
                break;
            case 'run':
                if(this.img !== this.sprites.run.img){
                    this.img = this.sprites.run.img;
                    this.totalFrames = this.sprites.run.totalFrames;
                    this.currentFrame = 0;
                }
                break;
             case 'jump':
                if(this.img !== this.sprites.jump.img){
                    this.img = this.sprites.jump.img;
                    this.totalFrames = this.sprites.jump.totalFrames;
                    this.currentFrame = 0;
                }
                break;
            case 'fall':
                if(this.img !== this.sprites.fall.img){
                    this.img = this.sprites.fall.img;
                    this.totalFrames = this.sprites.fall.totalFrames;
                    this.currentFrame = 0;
                }
                break;
            default:
                break;
        }
    }
}

export default playerSprite;