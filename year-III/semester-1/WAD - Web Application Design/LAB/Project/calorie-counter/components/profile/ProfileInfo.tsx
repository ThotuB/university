import { ProfileDto } from "types/profile";

interface ProfileInfoProps {
    info: ProfileDto;
}

export default function ProfileInfo({ info: { uid, name, email, image, phone, website, bio }}: ProfileInfoProps) {
    return (
        <div className="flex flex-col rounded-xl overflow-hidden gap-8">
            <div className="relative">
                <div className="absolute rounded-full overflow-hidden h-40 w-40 -bottom-12 left-8">
                    <img className="w-full object-cover" src={image} />
                </div>
                <div className="h-48 bg-gradient-to-r from-purple-300 to-red-300" />
            </div>
            <div className="p-6 flex justify-between">
                <div className="flex flex-col gap-2">
                    <div className="font-bold text-3xl">
                        {name}
                    </div>
                    <div>
                        {bio}
                    </div>
                </div>
                <div className="">
                    {website}
                </div>
            </div>
        </div>
    )
}
