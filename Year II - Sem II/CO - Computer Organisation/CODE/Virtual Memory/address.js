class Address {
    constructor(){
        this.sideLen = 10;
    }

    printBoxes(color, size){
        fill(color);
        noStroke();
        for (let i = 0 ; i < size ; i++){
            rect(0, 0, this.sideLen, this.sideLen);
            translate(this.sideLen, 0);
        }
    }

    printAllBoxes(...tags){
        push();
        for (let tag in tags){
            //print(tag);
        }
        pop();
        translate(0, this.sideLen);
    }
}

class VirtualAddress extends Address{
    constructor(tag, index, page){
        super();
        this.tag = tag;
        this.index = index;
        this.page = page;

        this.size = tag + index + page;
    }

    print(){
        super.printAllBoxes(this.tag, this.index, this.page);
        virtualAddressTagSizeText.html("< " + this.tag + " >");
        virtualAddressIndexSizeText.html("< " + this.index + " >");
        virtualAddressPageSizeText.html("< " + this.page + " >");
    }
}

class PhysicalAddress extends Address{
    constructor(tag, page){
        super();
        this.tag = tag;
        this.page = page;

        this.size = tag + page;
    }

    print(){
        super.printAllBoxes(this.tag, this.page);
        physicalAddressTagSizeText.html("< " + this.tag + " >");
        physicalAddressPageSizeText.html("< " + this.page + " >");
    }
}