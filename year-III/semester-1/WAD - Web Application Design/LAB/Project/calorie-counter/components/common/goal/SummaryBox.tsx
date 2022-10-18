interface SummaryBoxProps {
    value: number;
    label: string;
}

function SummaryBox({ value, label }: SummaryBoxProps) {
    return (
        <div className="flex flex-col w-16">
            <div className="text-gray-700 text-xl font-mono font-bold">
                {value}
            </div>
            <div className="text-gray-500 text-xs font-semibold">
                {label}
            </div>
        </div>
    )
}

export default SummaryBox;