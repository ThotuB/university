class Address {
    constructor(tag, index, block, word, unit){
        this.unit = unit;

        this.tag = tag;
        this.index = index;
        this.block = block;
        this.word = word;

        this.calcSizes();
        this.updateHTML();
    }

    calcSizes(){
        switch ( this.unit ){
            case AdrsUnits.BYTE:
                this.size = this.tag + this.index + this.block + this.word;
                break;
            case AdrsUnits.WORD:
                this.size = this.tag + this.index + this.block;
                break;
        }

        this.boxSize = width / ( this.size * 1.2 + 0.2);
    }

    updateHTML(){
        tagSizeOutput.html("< " + this.tag + " >");
        indexSizeOutput.html("< " + this.index + " >");
        blockSizeOutput.html("< " + this.block + " >");

        switch ( this.unit ){
            case AdrsUnits.BYTE:
                addressableUnitText.html("BYTE OFFSET");
                wordSizeOutput.html("< " + this.word + " >");
                break;
            case AdrsUnits.WORD:
                addressableUnitText.html("");
                wordSizeOutput.html("");
                break;
        }
    }

    print_bit(bit, box){
        text(bit, this.boxSize * 1.2 * (box-1), 0);
    }

    print_address(address){
        fill(0)
            .textStyle(BOLD)
            .textSize(25);
        translate(this.boxSize/2 - 5, this.boxSize - 5);

        address = parseInt(address, 16);
        if ( this.unit == AdrsUnits.BYTE ){
            tagOutput.html((address >>> (this.index + this.block + this.word)) % Math.pow(2, this.tag));
            indexOutput.html((address >>> (this.block + this.word)) % Math.pow(2, this.index));
            blockOutput.html((address >>> this.word) % Math.pow(2, this.block));
            wordOutput.html(address % Math.pow(2, this.word));
        }
        else {
            tagOutput.html((address >>> (this.index + this.block)) % Math.pow(2, this.tag));
            indexOutput.html((address >>> (this.block)) % Math.pow(2, this.index));
            blockOutput.html(address % Math.pow(2, this.block));
            wordOutput.html("");
        }

        for (let i = this.size ; i != 0 ; i--){
            this.print_bit(address & 1, i);
            address >>>= 1;
        }
    }

    print_box(color, size){
        fill(color);
        for (let i = 0; i < size; i++) {
            rect(0, 0, this.boxSize, this.boxSize, 5, 5, 5, 5);
            translate(this.boxSize * 1.2, 0);
        }
    }

    print_boxes(){
        translate(0.2 * this.boxSize, 0.2 * this.boxSize);
        push();
        this.print_box(color(255, 200, 255), this.tag);
        this.print_box(color(200, 150, 255), this.index);
        this.print_box(color(255, 100, 255), this.block);
        this.print_box(color(200, 50, 255), this.word);
        pop();
    }
}