interface CarouselProps {
    children: any[];
    index: number;
    onChange: (index: number) => void;
}

export default function Carousel({ children, index, onChange }: CarouselProps) {


    return (
        <div className="flex flex-col gap-2 items-center">
            <div className="max-h-96 max-w-5xl overflow-hidden flex justify-center rounded-2xl trans">
                {children[index]}
            </div>
            <div className="flex gap-4 bottom-2">
                {children.map((child, idx) => (
                    <div className={`rounded-full ${(index === idx) ? 'bg-purple-300' : 'bg-red-300'} w-5 h-5 cursor-pointer`}
                        onClick={() => onChange(idx)}
                    />
                ))}
            </div>
        </div>
    )
}