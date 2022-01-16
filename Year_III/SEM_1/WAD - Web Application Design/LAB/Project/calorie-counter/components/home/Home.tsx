import Carousel from 'components/common/Carousel'
import { useState } from 'react'

const images = [
    "https://images.unsplash.com/photo-1540189549336-e6e99c3679fe?ixlib=rb-1.2.1&ixid=MnwxMjA3fDB8MHxleHBsb3JlLWZlZWR8Mnx8fGVufDB8fHx8&w=1000&q=80",
    "https://images-prod.healthline.com/hlcmsresource/images/AN_images/healthy-eating-ingredients-1296x728-header.jpg",
    "https://www.wbcsd.org/var/site/storage/images/media/images/fresh_pa/80809-2-eng-GB/FRESH_PA_i1140.jpg",
    "https://www.myfoodtrip.com/wp-content/uploads/2020/05/Food-Blog-Directory.jpg",
    "https://s.marketwatch.com/public/resources/images/MW-HS676_fastfo_ZG_20191004102654.jpg"
]

export default function Home() {
    const [index, setIndex] = useState(0)

    return (
        <>
            <Carousel index={index} onChange={setIndex}>
                {images.map((image, index) => (
                    <img key={index} src={image} className="object-cover" />
                ))}
            </Carousel>
        </>
    )
}