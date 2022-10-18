import { AddPhoto } from 'components/common/svg/Icons';

// no children
interface ImageFieldProps {
    onImageChange: (image: File | null) => void;
}

export default ({ onImageChange }: ImageFieldProps) => (
    <div className="text-sm border-2 border-dashed border-gray-300 rounded-md p-4 flex flex-col items-center">
        <AddPhoto />
        <div className="text-gray-700">
            <label className="font-semibold text-purple-600 hover:text-purple-400 ">
                Upload a file
                <input type="file" className="sr-only"
                    onChange={(e) => onImageChange(e.target.files?.[0] ?? null)}
                />
            </label>
            {" "}or drag and drop
        </div>
        <div className="text-gray-500">
            PNG, JPG up to 5MB
        </div>
    </div>
);