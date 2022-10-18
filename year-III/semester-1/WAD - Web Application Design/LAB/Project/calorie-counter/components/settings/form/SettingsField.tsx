import TextField from "components/common/TextField";

interface EditProfileFieldProps {
    label?: string;
    children: React.ReactNode;
}

export default function EditProfileField({ label, children }: EditProfileFieldProps) {
    return (
        <>
            <div className="text-gray-800 font-bold text-right">
                {label}
            </div>
            <div className="col-span-4">
                {children}
            </div>
        </>
    )


}
