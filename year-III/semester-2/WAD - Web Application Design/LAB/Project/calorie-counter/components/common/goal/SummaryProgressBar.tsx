interface SummaryProgressBarProps {
    children: React.ReactNode;
    perc: number;
    percPrev: number;
    className: string;
}

function SummaryProgressBar({ children, perc, percPrev, className }: SummaryProgressBarProps) {
    const percLeft = 100 - percPrev;

    function printTextIf() {
        if ( perc - percPrev > 15 ){
            return children;
        }
    }

    return (
        <div className={`rounded-xl absolute h-full flex justify-end w-0 ${className}`}
            style={{ width: `${perc}%` }}
        >
            <div className="flex justify-center items-center font-semibold"
                style={{ width: `${percLeft}%` }}
            >
                {printTextIf()}
            </div>
        </div>
    )
}

export default SummaryProgressBar;