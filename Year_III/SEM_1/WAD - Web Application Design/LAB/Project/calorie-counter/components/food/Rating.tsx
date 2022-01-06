import { Star } from '../common/svg/Icons'

function Rating(props) {
    let { rating } = props;

    const stars = [];
    for (let i = 0; i < 5; i++) {
        stars[i] = <Star
            key={i}
            fill={
                i < rating - 0.5 ? "full" 
                    : i < rating ? "half"
                        : "none"
            }
        />
    }

    return (
        <div className="flex item-center">
            {stars}
        </div>
    );
}

export default Rating;