function SummaryProgressBar(props) {
    const { perc, percPrev, className } = props;
    const percLeft = 100 - percPrev;

    function printTextIf() {
        if ( perc - percPrev > 15 ){
            return props.children;
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